#pragma once

#include <cstddef>
#include <stdexcept>

namespace huffman {

using std::size_t;

class invalid_file_format : public std::runtime_error {
public:
	invalid_file_format(const char *msg): std::runtime_error(msg) {}
};

struct HuffFileData {
	size_t input_sz = 0;
	size_t output_sz = 0;
	size_t additional_sz = 0;

	HuffFileData() {}
	HuffFileData(size_t in, size_t out, size_t add): input_sz(in), output_sz(out), additional_sz(add) {}
};

}