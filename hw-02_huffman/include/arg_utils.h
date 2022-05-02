#pragma once

#include <string_view>
#include <optional>

namespace arg_utils {

struct Arguments {
public:
	std::string_view get_target();
	std::string_view get_input_file();
	std::string_view get_output_file();

	void set_target(const std::string_view &tg);
	void set_input_file(const std::string_view &inf);
	void set_output_file(const std::string_view &ouf);

	friend Arguments process_args(int argc, const char **argv);

private:
	std::optional <std::string_view> target;
	std::optional <std::string_view> input_file;
	std::optional <std::string_view> output_file;
};

Arguments process_args(int argc, const char **argv);

}