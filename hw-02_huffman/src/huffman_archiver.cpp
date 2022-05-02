#include "huffman_archiver.h"
#include <iostream>

namespace huffman {

using huff_tree::CHARS_CNT;

HuffFileData HuffmanArchiver::archive(std::istream &in, std::ostream &out) {
	CharCounter cnt;
	count_chars(in, cnt);
	htree.rebuild(cnt);

	in.clear(); in.seekg(in.beg);
	
	BitOutputStream bo(out);
	size_t additional_sz = save_tree(bo) + sizeof(size_t);
	write_file_size(cnt, bo);
	size_t input_sz = compress_file(in, bo);
	size_t output_sz = (calc_file_size(cnt) + CHAR_BIT - 1) / CHAR_BIT;

	return HuffFileData(input_sz, output_sz, additional_sz);
}

void HuffmanArchiver::count_chars(std::istream &in, CharCounter &cnt) const {
	char buf;
	while (in.read(&buf, 1)) {
		cnt.add_char(buf);
	}
}

size_t HuffmanArchiver::save_tree(BitOutputStream &bo) const {
	std::vector <bool> tree = htree.get_compressed_tree();
	for (bool b : tree) {
		bo.write_bit(b);
	}

	size_t ceiled_tree_size_in_bytes = (tree.size() + CHAR_BIT - 1) / CHAR_BIT;
	size_t tree_tail_bits = ceiled_tree_size_in_bytes * CHAR_BIT - tree.size();
	for (size_t i = 0; i < tree_tail_bits; i++) {
		bo.write_bit(0);
	}

	return ceiled_tree_size_in_bytes;
}

size_t HuffmanArchiver::compress_file(std::istream &in, BitOutputStream &bo) const {
	char buf;
	size_t file_sz = 0;
	while (in.read(&buf, 1)) {
		file_sz++;
		
		const std::vector <bool> &code = htree.get_char_code((unsigned char)buf);
		for (bool b : code) {
			bo.write_bit(b);
		}
	}
	return file_sz;
}

size_t HuffmanArchiver::calc_file_size(const CharCounter &cnt) const {
	size_t result = 0;
	for (size_t i = 0; i < CHARS_CNT; i++) {
		result += cnt.get_char_cnt(i) * htree.get_char_code(i).size();
	}
	return result;
}

void HuffmanArchiver::write_file_size(const CharCounter &cnt, BitOutputStream &bo) const {
	size_t sz = calc_file_size(cnt);
	for (size_t i = 0; i < sizeof(sz) * CHAR_BIT; i++) {
		bo.write_bit(sz & ((size_t)1 << i));
	}
}

}