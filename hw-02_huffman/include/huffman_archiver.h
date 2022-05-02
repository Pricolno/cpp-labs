#pragma once

#include "hufftree.h"
#include "huffman_util.h"
#include "bitio.h"
#include <iosfwd>

namespace huffman {

using std::size_t;
using huff_tree::CharCounter;
using huff_tree::HuffTree;
using bit_io::BitOutputStream;

class HuffmanArchiver {
public:
	HuffFileData archive(std::istream &in, std::ostream &out);

private:
	HuffTree htree;

	void count_chars(std::istream &in, CharCounter &cnt) const;
	size_t save_tree(BitOutputStream &bo) const;
	size_t compress_file(std::istream &in, BitOutputStream &bo) const;
	size_t calc_file_size(const CharCounter &cnt) const;
	void write_file_size(const CharCounter &cnt, BitOutputStream &bo) const;
};

}