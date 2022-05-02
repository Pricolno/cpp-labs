#include "hufftree.h"
#include "huffman_util.h"
#include <cassert>

namespace huff_tree {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharCounter::CharCounter() {}

CharCounter::~CharCounter() {}

void CharCounter::add_char(char ch) {
	char_cnt[(unsigned char)ch]++;
}

size_t CharCounter::get_char_cnt(unsigned char ch) const {
	return char_cnt[ch];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HuffTree::Node::Node(): l(nullptr), r(nullptr), weight(0), ch(0) {}

HuffTree::Node::Node(size_t w, unsigned char c): l(nullptr), r(nullptr), weight(w), ch(c) {}

HuffTree::Node::Node(Node *left, Node *right): l(left), r(right), weight(0), ch(0) {
	if (l) {
		weight += l->weight;
	}
	if (r) {
		weight += r->weight;
	}
}

HuffTree::Node::~Node() {
	delete l; delete r;
}

bool HuffTree::Node::term() const {
	return l == nullptr && r == nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HuffTree::HuffTree() {}

HuffTree::~HuffTree() {
	delete root;
}

void HuffTree::rebuild(const CharCounter &ccntr) {
	delete root;

	std::array <Node*, CHARS_CNT> roots;
	size_t sz = CHARS_CNT;
	for (size_t i = 0; i < sz; i++) {
		roots[i] = new Node(ccntr.get_char_cnt(i), i);
	}

	while (sz > 1) {
		std::pair <size_t, size_t> cur = find_two_minimums(roots, sz);
		Node *new_node = new Node(roots[cur.first], roots[cur.second]);

		roots[cur.first] = new_node;
		std::swap(roots[cur.second], roots[sz - 1]);
		sz--;
	}

	root = roots[0];
	build_char_codes();
}

void HuffTree::rebuild(const std::vector <unsigned char> &ch_perm, const std::vector <bool> &tree) {
	delete root;
	root = new Node();
	std::vector <Node*> stck = {root};
	size_t ptr = 0;

	try {
		for (bool step : tree) {
			if (stck.empty()) {
				throw huffman::invalid_file_format("tree processing failure");
			}
			Node *cur = stck.back();

			if (!step) {
				if (cur->l == nullptr) {
					cur->l = new Node();
					stck.push_back(cur->l);
				} else if (cur->r == nullptr) {
					cur->r = new Node();
					stck.push_back(cur->r);
				} else {
					throw huffman::invalid_file_format("tree node has more than 2 children");
				}
			} else {
				stck.pop_back();

				if (cur->term()) {
					cur->ch = ch_perm.at(ptr++);
				} else if (cur->l == nullptr || cur->r == nullptr) {
					throw huffman::invalid_file_format("tree node has less than 2 children");
				}
			}
		}
	} catch (std::out_of_range &e) {
		throw huffman::invalid_file_format("tree has too many characters");
	}

	if (stck.size() != 1 || stck[0] != root) {
		throw huffman::invalid_file_format("tree processing failure");
	}
	if (ptr != ch_perm.size()) {
		throw huffman::invalid_file_format("tree has too few characters");
	}
}

std::vector <bool> HuffTree::get_compressed_tree() const {
	std::vector <bool> tree;
	get_tree_chars(root, tree);
	get_tree_tour(root, tree);
	return tree;
}

const std::vector <bool>& HuffTree::get_char_code(unsigned char ch) const {
	return char_code[ch];
}

HuffTree::Node const * HuffTree::get_root() const {
	return root;
}

std::pair <size_t, size_t> HuffTree::find_two_minimums(const std::array <Node*, CHARS_CNT> &roots, size_t sz) const {
	assert(sz >= 2);

	std::pair <size_t, size_t> result = {0, 1};
	if (roots[0]->weight > roots[1]->weight) {
		result = {1, 0};
	}

	for (size_t i = 2; i < sz; i++) {
		if (roots[i]->weight <= roots[result.first]->weight) {
			result.second = result.first; result.first = i;
		} else if (roots[i]->weight < roots[result.second]->weight) {
			result.second = i;
		}
	}

	assert(result.first != result.second);
	
	return result;
}

void HuffTree::build_char_codes() {
	const size_t sz = CHARS_CNT;
	for (size_t i = 0; i < sz; i++) {
		std::vector <bool> ().swap(char_code[i]);
	}

	std::vector <bool> cur_code;
	build_char_codes_dfs(root, cur_code);
}

void HuffTree::build_char_codes_dfs(Node *v, std::vector <bool> &cur_code) {
	if (v->term()) {
		std::copy(cur_code.begin(), cur_code.end(), std::back_inserter(char_code[v->ch]));
	}

	if (v->l != nullptr) {
		cur_code.push_back(false);
		build_char_codes_dfs(v->l, cur_code);
		cur_code.pop_back();
	}
	if (v->r != nullptr) {
		cur_code.push_back(true);
		build_char_codes_dfs(v->r, cur_code);
		cur_code.pop_back();
	}
}

void HuffTree::get_tree_chars(Node *v, std::vector <bool> &chars) const {
	if (v->term()) {
		for (size_t i = 0; i < CHAR_BIT; i++) {
			chars.push_back(v->ch & (1 << i));
		}
	}

	if (v->l != nullptr) {
		get_tree_chars(v->l, chars);
	}
	if (v->r != nullptr) {
		get_tree_chars(v->r, chars);
	}
}

void HuffTree::get_tree_tour(Node *v, std::vector <bool> &tree) const {
	if (v->l != nullptr) {
		tree.push_back(0);
		get_tree_tour(v->l, tree);
		tree.push_back(1);
	}
	if (v->r != nullptr) {
		tree.push_back(0);
		get_tree_tour(v->r, tree);
		tree.push_back(1);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}