#pragma once

#include "hufftree.h"
#include "huffman_util.h"
#include "bitio.h"
#include <iosfwd>

namespace huffman {

using std::size_t;
using huff_tree::HuffTree;
using bit_io::BitInputStream;

class HuffmanDearchiver {
public:
	HuffFileData dearchive(std::istream &in, std::ostream &out);

private:
	HuffTree htree;

	std::vector <unsigned char> get_char_permutation_from_archive(std::istream &in) const;
	std::vector <bool> get_tree_tour(BitInputStream &bi) const;
	size_t read_file_size(BitInputStream &bi) const;
	size_t decompress_file(BitInputStream &bi, size_t input_sz, std::ostream &out) const;
};

}