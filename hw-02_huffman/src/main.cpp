#include "huffman.h"
#include "arg_utils.h"
#include <iostream>
#include <fstream>

using arg_utils::Arguments;
using arg_utils::process_args;

static huffman::HuffFileData archive(const std::string_view &input, const std::string_view &output) {
	std::ifstream in(input.data());
	if (in.fail()) {
		throw std::invalid_argument("Input file doesn't exist or can't be opened");
	}

	std::ofstream out(output.data());
	if (out.fail()) {
		throw std::invalid_argument("Output file can't be opened");
	}
	
	huffman::HuffmanArchiver a;
	return a.archive(in, out);
}

static huffman::HuffFileData dearchive(const std::string_view &input, const std::string_view &output) {
	std::ifstream in(input.data());
	if (in.fail()) {
		throw std::invalid_argument("Input file doesn't exist or can't be opened");
	}

	std::ofstream out(output.data());
	if (out.fail()) {
		throw std::invalid_argument("Output file can't be opened");
	}

	huffman::HuffmanDearchiver d;
	return d.dearchive(in, out);
}

int main(int argc, char **argv) {
	try {
		Arguments args = process_args(argc, (const char**)argv);

		huffman::HuffFileData data;
		if (args.get_target() == "-c") {
			data = archive(args.get_input_file(), args.get_output_file());
		} else {
			data = dearchive(args.get_input_file(), args.get_output_file());
		}

		std::cout << data.input_sz << std::endl;
		std::cout << data.output_sz << std::endl;
		std::cout << data.additional_sz << std::endl;

	} catch (std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
		return 1;

	} catch (huffman::invalid_file_format &e) {
		std::cerr << "Invalid archive format!" << std::endl;
		std::cerr << "Reason: " << e.what() << std::endl;
		return 2;

	} catch (std::exception &e) {
		std::cerr << "Fatal error!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 3;

	}

	return 0;
}