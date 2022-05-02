#pragma once

#include <cstdint>
#include <climits>
#include <vector>
#include <array>

namespace huff_tree {

using std::size_t;
const size_t CHARS_CNT = 1 << CHAR_BIT;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CharCounter {
public:
	CharCounter();
	~CharCounter();

	void add_char(char ch);

	size_t get_char_cnt(unsigned char ch) const;

private:
	size_t char_cnt[CHARS_CNT]{};
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class HuffTree {
public:
	HuffTree();
	~HuffTree();

	void rebuild(const CharCounter &ccntr);
	void rebuild(const std::vector <unsigned char> &ch_perm, const std::vector <bool> &tree);

	std::vector <bool> get_compressed_tree() const;
	const std::vector <bool>& get_char_code(unsigned char ch) const;

	class Node {
	public:
		Node *l, *r;
		size_t weight;
		unsigned char ch;

		Node();
		Node(size_t w, unsigned char c);
		Node(Node *left, Node *right);
		~Node();

		bool term() const;
	};

	Node const * get_root() const;

private:
	Node *root = nullptr;
	std::vector <bool> char_code[CHARS_CNT];

	std::pair <size_t, size_t> find_two_minimums(const std::array <Node*, CHARS_CNT> &roots, size_t sz) const;

	void build_char_codes();
	void build_char_codes_dfs(Node *v, std::vector <bool> &cur_code);
	void get_tree_chars(Node *v, std::vector <bool> &chars) const;
	void get_tree_tour(Node *v, std::vector <bool> &tree) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}