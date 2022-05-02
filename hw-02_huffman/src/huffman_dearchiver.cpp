#include "huffman_dearchiver.h"
#include <iostream>

namespace huffman {

using huff_tree::CHARS_CNT;

HuffFileData HuffmanDearchiver::dearchive(std::istream &in, std::ostream &out) {
	std::vector <unsigned char> ch_perm = get_char_permutation_from_archive(in);
	BitInputStream bi(in);
	std::vector <bool> tree = get_tree_tour(bi);
	htree.rebuild(ch_perm, tree);

	size_t additional_sz = ch_perm.size() + (tree.size() + CHAR_BIT - 1) / CHAR_BIT + sizeof(size_t);
	size_t input_sz_bits = read_file_size(bi);
	size_t input_sz = (input_sz_bits + CHAR_BIT - 1) / CHAR_BIT;
	size_t output_sz = decompress_file(bi, input_sz_bits, out);

	return HuffFileData(input_sz, output_sz, additional_sz);
}

std::vector <unsigned char> HuffmanDearchiver::get_char_permutation_from_archive(std::istream &in) const {
	char buf;
	std::vector <unsigned char> result;
	for (size_t i = 0; i < CHARS_CNT; i++) {
		if (!in.read(&buf, 1)) {
			throw invalid_file_format("error while reading char permutation");
		}
		result.push_back((unsigned char)buf);
	}
	return result;
}

std::vector <bool> HuffmanDearchiver::get_tree_tour(BitInputStream &bi) const {
	std::vector <bool> tree;
	const size_t tree_sz = CHARS_CNT * 2 - 1;
	size_t bits_read = 0;
	for (size_t i = 0; i < (tree_sz - 1) * 2; i++, bits_read++) {
		tree.push_back(bi.read_bit());
	}

	while (bits_read % CHAR_BIT != 0) {
		bi.read_bit();
		bits_read++;
	}

	return tree;
}

size_t HuffmanDearchiver::read_file_size(BitInputStream &bi) const {
	size_t result = 0;
	for (size_t i = 0, mask = 1; i < sizeof(size_t) * CHAR_BIT; i++, mask <<= 1) {
		if (bi.read_bit()) {
			result |= mask;
		}
	}
	return result;
}

size_t HuffmanDearchiver::decompress_file(BitInputStream &bi, size_t input_sz, std::ostream &out) const {
	size_t output_sz = 0;
	HuffTree::Node const *cur = htree.get_root();

	try {
		for (size_t i = 0; i < input_sz; i++) {
			if (!bi.read_bit()) {
				cur = cur->l;
			} else {
				cur = cur->r;
			}

			if (cur->term()) {
				char to_write = (char)cur->ch;
				out.write(&to_write, 1);
				output_sz++;
				cur = htree.get_root();
			}
		}
	} catch (std::istream::failure &e) {
		throw invalid_file_format("too few bits in input file");
	}

	if (cur != htree.get_root()) {
		throw invalid_file_format("unhandled chars at the end of file");
	}

	return output_sz;
}

}