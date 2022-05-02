#include "arg_utils.h"
#include <stdexcept>

namespace arg_utils {

std::string_view Arguments::get_target() {
	return target.value();
}

std::string_view Arguments::get_input_file() {
	return input_file.value();
}

std::string_view Arguments::get_output_file() {
	return output_file.value();
}

void Arguments::set_target(const std::string_view &tg) {
	if (target) {
		throw std::invalid_argument("Multiple targets (-c or -u)");
	}
	target = tg;
}

void Arguments::set_input_file(const std::string_view &inf) {
	if (input_file) {
		throw std::invalid_argument("Multiple input files (-f or --file)");
	}
	input_file = inf;
}

void Arguments::set_output_file(const std::string_view &ouf) {
	if (output_file) {
		throw std::invalid_argument("Multiple output files (-o or --output)");
	}
	output_file = ouf;
}

Arguments process_args(int argc, const char **argv) {
	Arguments result;
	for (int i = 1; i < argc; i++) {
		std::string_view cur(argv[i]);

		if (cur == "-c" || cur == "-u") {
			result.set_target(cur);

		} else if (cur == "-f" || cur == "--file") {
			if (i == argc - 1) {
				throw std::invalid_argument("Missing input file (-f)");
			}
			result.set_input_file(std::string_view(argv[i + 1]));

		} else if (cur == "-o" || cur == "--output") {
			if (i == argc - 1) {
				throw std::invalid_argument("Missing output file (-o)");
			}
			result.set_output_file(std::string_view(argv[i + 1]));
		}
	}

	if (!result.target) {
		throw std::invalid_argument("Missing target (-c or -u)");
	}
	if (!result.input_file) {
		throw std::invalid_argument("Missing input file (-f or --file)");
	}
	if (!result.output_file) {
		throw std::invalid_argument("Missing output file (-o or --output)");
	}
	if (result.get_input_file() == result.get_output_file()) {
		throw std::invalid_argument("Input and output files are the same");
	}

	return result;
}

}