#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../test_include/doctest.h"

#include "../../include/arg_utils.h"
#include "../../include/bitio.h"
#include "../../include/hufftree.h"
#include "../../include/huffman.h"
	
#include <cstddef>
#include <random>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>

using std::size_t;
using std::mt19937;
using std::vector;
using std::string;
using std::stringstream;
using std::istream;
using std::exception;
using std::invalid_argument;

using arg_utils::Arguments;
using arg_utils::process_args;

using bit_io::BitInputStream;
using bit_io::BitOutputStream;

using huff_tree::CHARS_CNT;
using huff_tree::CharCounter;
using huff_tree::HuffTree;

using huffman::HuffmanArchiver;
using huffman::HuffmanDearchiver;
using huffman::HuffFileData;
using huffman::invalid_file_format;

TEST_CASE("LOL"){
	CHECK(1 == 1);
	CHECK(false == 0);
	//CHECK(true == 0);
	CHECK(2 == 2);

}

TEST_SUITE("test arg_utils") {
	TEST_CASE("test missing target") {
		const size_t N = 5;
		const char *argv[N]{"hw_02", "-f", "a", "-o", "b"};

		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}


	TEST_CASE("test multiple targets 1") {
		const size_t N = 7;
		const char *argv[N]{"hw_02", "-c", "-u", "-f", "a", "-o", "b"};
	
		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}

	TEST_CASE("test multiple targets 2") {
		const size_t N = 7;
		const char *argv[N]{"hw_02", "-c", "-c", "-f", "a", "-o", "b"};
		
		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}

	TEST_CASE("test missing input file") {
		const size_t N = 4;
		const char *argv[N]{"hw_02", "-c", "-o", "b"};
		
		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}

		TEST_CASE("test multiple input files 1") {
		const size_t N = 8;
		const char *argv[N]{"hw_02", "-c", "-f", "a", "-f", "b", "-o", "c"};
		
		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}


	TEST_CASE("test multiple input files 2") {
		const size_t N = 8;
		const char *argv[N]{"hw_02", "-c", "-f", "a", "--file", "b", "-o", "c"};
		
		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}


	TEST_CASE("test missing output file") {
		const size_t N = 4;
		const char *argv[N]{"hw_02", "-c", "-f", "a"};
		
		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}

	TEST_CASE("test multiple output files 1") {
		const size_t N = 8;
		const char *argv[N]{"hw_02", "-c", "-f", "a", "-o", "b", "-o", "c"};
		
		CHECK_THROWS_AS(process_args(N, argv), invalid_argument);
	}

	TEST_CASE("test correct input 2") {
		const size_t N = 6;
		const char *argv[N]{"hw_02", "-c", "--file", "a", "-o", "b"};
		
		Arguments args = process_args(N, argv);
		CHECK(args.get_target() == "-c");
		CHECK(args.get_input_file() == "a");
		CHECK(args.get_output_file() == "b");
	}

	TEST_CASE("test correct input 3") {
		const size_t N = 6;
		const char *argv[N]{"hw_02", "-c", "-f", "a", "--output", "b"};
		
		Arguments args = process_args(N, argv);
		CHECK(args.get_target() == "-c");
		CHECK(args.get_input_file() == "a");
		CHECK(args.get_output_file() == "b");
	}


	TEST_CASE("test correct input 4") {
		const size_t N = 6;
		const char *argv[N]{"hw_02", "-u", "-f", "a", "-o", "b"};
		
		Arguments args = process_args(N, argv);
		CHECK(args.get_target() == "-u");
		CHECK(args.get_input_file() == "a");
		CHECK(args.get_output_file() == "b");
	}


	TEST_CASE("test correct input 5") {
		const size_t N = 6;
		const char *argv[N]{"hw_02", "-u", "-o", "b", "--file", "a"};
		
		Arguments args = process_args(N, argv);
		CHECK(args.get_target() == "-u");
		CHECK(args.get_input_file() == "a");
		CHECK(args.get_output_file() == "b");
	}
}


TEST_SUITE("test bit_io") {
	TEST_CASE("test bit_io 1") {
		const size_t N = 24;
		bool arr[N]{1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0};

		stringstream str;

		{
			BitOutputStream bo(str);
			for (size_t i = 0; i < N; i++) {
				bo.write_bit(arr[i]);
			}
		}

		BitInputStream bi(str);
		for (size_t i = 0; i < N; i++) {
			CHECK(bi.read_bit() == arr[i]);
		}
	}


	TEST_CASE("test bit_io 2") {
		const size_t N = 26;
		bool arr[N]{0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1};

		stringstream str;

		{
			BitOutputStream bo(str);
			for (size_t i = 0; i < N; i++) {
				bo.write_bit(arr[i]);
			}
		}

		BitInputStream bi(str);
		for (size_t i = 0; i < N; i++) {
			CHECK(bi.read_bit() == arr[i]);
		}
	}


	TEST_CASE("test bit_io 3") {
		stringstream str;

		{
			BitOutputStream bo(str);
			bo.write_bit(0);
			bo.write_bit(1);
			bo.write_bit(0);
			bo.write_bit(1);
			bo.write_bit(0);
			bo.write_bit(1);
			bo.write_bit(0);
		}

		BitInputStream bi(str);
		for (size_t i = 0; i < 7; i++) {
			CHECK(bi.read_bit() == (i & 1));
		}
		bi.read_bit();

		CHECK_THROWS_WITH_AS(bi.read_bit(), "no bits left in input: iostream error", istream::failure);
	}
}



TEST_SUITE("test CharCounter") {
	TEST_CASE("test 1") {
		CharCounter cnt;
		string res = "Hello, world!";

		for (char c : res) {
			cnt.add_char(c);
		}

		CHECK(cnt.get_char_cnt('H') == 1);
		CHECK(cnt.get_char_cnt('e') == 1);
		CHECK(cnt.get_char_cnt('l') == 3);
		CHECK(cnt.get_char_cnt('o') == 2);
		CHECK(cnt.get_char_cnt(',') == 1);
		CHECK(cnt.get_char_cnt(' ') == 1);
		CHECK(cnt.get_char_cnt('w') == 1);
		CHECK(cnt.get_char_cnt('r') == 1);
		CHECK(cnt.get_char_cnt('d') == 1);
		CHECK(cnt.get_char_cnt('!') == 1);
	}


	TEST_CASE("test 2") {
		CharCounter cnt;
		string res = "Huffman algo";

		for (char c : res) {
			cnt.add_char(c);
		}

		CHECK(cnt.get_char_cnt('H') == 1);
		CHECK(cnt.get_char_cnt('u') == 1);
		CHECK(cnt.get_char_cnt('f') == 2);
		CHECK(cnt.get_char_cnt('m') == 1);
		CHECK(cnt.get_char_cnt('a') == 2);
		CHECK(cnt.get_char_cnt('n') == 1);
		CHECK(cnt.get_char_cnt(' ') == 1);
		CHECK(cnt.get_char_cnt('l') == 1);
		CHECK(cnt.get_char_cnt('g') == 1);
		CHECK(cnt.get_char_cnt('o') == 1);
	}

	TEST_CASE("test 3") {
		CharCounter cnt;
		for (size_t i = 0; i < CHARS_CNT; i++) {
			CHECK(cnt.get_char_cnt(i) == 0);
		}
	}
}


TEST_SUITE("test HuffTree") {
	const size_t TREE_SZ = CHARS_CNT * 2 - 1;

	void load_chars(CharCounter &cnt, mt19937 &mtw, size_t mod = 256, size_t N = 10000) {
		for (size_t i = 0; i < N; i++) {
			char c = mtw() % mod;
			cnt.add_char(c);
		}
	}

	size_t get_full_length(const CharCounter &cnt, const HuffTree &t) {
		size_t sz = 0;
		for (size_t i = 0; i < CHARS_CNT; i++) {
			sz += cnt.get_char_cnt(i) * t.get_char_code(i).size();
		}
		return sz;
	}

	vector <bool> get_bit_char_seq(vector <unsigned char> &s) {
		vector <bool> result;
		for (auto c : s) {
			for (size_t i = 0; i < CHAR_BIT; i++) {
				result.push_back(c & (1ll << i));
			}
		}
		return result;
	}

	vector <unsigned char> gen_char_permutation(mt19937 &mtw) {
		vector <unsigned char> p(CHARS_CNT);
		std::iota(p.begin(), p.end(), 0); std::shuffle(p.begin(), p.end(), mtw);
		return p;
	}

	vector <bool> gen_random_tree(mt19937 &mtw) {
		vector <int> gr[TREE_SZ], cur_v(CHARS_CNT);
		std::iota(cur_v.begin(), cur_v.end(), 0);
		size_t p = CHARS_CNT;

		while (cur_v.size() > 1) {
			int a = mtw() % (cur_v.size() - 1) + 1;
			int b = mtw() % a;
			
			gr[p] = {cur_v[a], cur_v[b]};
			cur_v.erase(cur_v.begin() + a);
			cur_v.erase(cur_v.begin() + b);
			cur_v.push_back(p++);
		}

		vector <bool> result;
		std::function<void(int)> dfs = [&](int v) -> void {
			for (int u : gr[v]) {
				result.push_back(0);
				dfs(u);
				result.push_back(1);
			}
		};
		dfs(cur_v[0]);

		return result;
	}

	TEST_CASE("test rebuild 1") {
		HuffTree t;
		CharCounter cnt;
		mt19937 mtw(1);

		load_chars(cnt, mtw);
		t.rebuild(cnt);

		CHECK(get_full_length(cnt, t) == 79974);
	}

	TEST_CASE("test rebuild 2") {
		HuffTree t;
		CharCounter cnt;
		mt19937 mtw(2);

		load_chars(cnt, mtw);
		t.rebuild(cnt);

		CHECK(get_full_length(cnt, t) == 79991);
	}

	TEST_CASE("test rebuild 3") {
		HuffTree t;
		CharCounter cnt;
		mt19937 mtw(3);
		
		load_chars(cnt, mtw, 2);
		t.rebuild(cnt);

		CHECK(get_full_length(cnt, t) == 14968);
	}

	TEST_CASE("test rebuild 4") {
		HuffTree t;
		CharCounter cnt;
		mt19937 mtw(4);
		
		load_chars(cnt, mtw, 5);
		t.rebuild(cnt);

		CHECK(get_full_length(cnt, t) == 25952);
	}

	TEST_CASE("test tree length") {
		HuffTree t;
		CharCounter cnt;
		mt19937 mtw(22);

		load_chars(cnt, mtw);

		t.rebuild(cnt);
		CHECK(t.get_compressed_tree().size() == 3068);

		t.rebuild(cnt);
		CHECK(t.get_compressed_tree().size() == 3068);

		t.rebuild(cnt);
		CHECK(t.get_compressed_tree().size() == 3068);

		t.rebuild(cnt);
		CHECK(t.get_compressed_tree().size() == 3068);
	}

	TEST_CASE("test rebuild from file with get_compressed_tree") {
		HuffTree t;
		mt19937 mtw(24);

		vector <unsigned char> p = gen_char_permutation(mtw);
		vector <bool> tree = gen_random_tree(mtw);

		t.rebuild(p, tree);

		vector <bool> compressed = get_bit_char_seq(p);
		std::copy(tree.begin(), tree.end(), std::back_inserter(compressed));

		CHECK(compressed == t.get_compressed_tree());
	}
}


TEST_SUITE("test HuffmanArchiver and HuffmanDearchiver") {
	const size_t TREE_SZ = CHARS_CNT * 2 - 1;

	vector <unsigned char> gen_char_permutation(mt19937 &mtw) {
		vector <unsigned char> p(CHARS_CNT);
		std::iota(p.begin(), p.end(), 0); std::shuffle(p.begin(), p.end(), mtw);
		return p;
	}

	vector <bool> gen_random_tree(mt19937 &mtw) {
		vector <int> gr[TREE_SZ], cur_v(CHARS_CNT);
		std::iota(cur_v.begin(), cur_v.end(), 0);
		size_t p = CHARS_CNT;

		while (cur_v.size() > 1) {
			int a = mtw() % (cur_v.size() - 1) + 1;
			int b = mtw() % a;
			
			gr[p] = {cur_v[a], cur_v[b]};
			cur_v.erase(cur_v.begin() + a);
			cur_v.erase(cur_v.begin() + b);
			cur_v.push_back(p++);
		}

		vector <bool> result;
		std::function<void(int)> dfs = [&](int v) -> void {
			for (int u : gr[v]) {
				result.push_back(0);
				dfs(u);
				result.push_back(1);
			}
		};
		dfs(cur_v[0]);

		return result;
	}

	TEST_CASE("test statistics 1") {
		stringstream src, arch, res;
		src << "Hello, World!";

		HuffmanArchiver a;
		HuffFileData x = a.archive(src, arch);

		HuffmanDearchiver d;
		HuffFileData y = d.dearchive(arch, res);

		CHECK(src.str().size() == x.input_sz);
		CHECK(arch.str().size() == x.output_sz + x.additional_sz);
		CHECK(x.input_sz == y.output_sz);
		CHECK(x.output_sz == y.input_sz);
		CHECK(x.additional_sz == y.additional_sz);
	}

	TEST_CASE("test statistics 2") {
		stringstream src, arch, res;
		src << "ahahahahahahahhahahahahahahahahahahahaha";

		HuffmanArchiver a;
		HuffFileData x = a.archive(src, arch);

		HuffmanDearchiver d;
		HuffFileData y = d.dearchive(arch, res);

		CHECK(src.str().size() == x.input_sz);
		CHECK(arch.str().size() == x.output_sz + x.additional_sz);
		CHECK(x.input_sz == y.output_sz);
		CHECK(x.output_sz == y.input_sz);
		CHECK(x.additional_sz == y.additional_sz);
	}

	TEST_CASE("test statistics 3") {
		stringstream src, arch, res;
		src << "kek";

		HuffmanArchiver a;
		HuffFileData x = a.archive(src, arch);

		HuffmanDearchiver d;
		HuffFileData y = d.dearchive(arch, res);

		CHECK(src.str().size() == x.input_sz);
		CHECK(arch.str().size() == x.output_sz + x.additional_sz);
		CHECK(x.input_sz == y.output_sz);
		CHECK(x.output_sz == y.input_sz);
		CHECK(x.additional_sz == y.additional_sz);
	}


	TEST_CASE("test empty file statistics") {
		stringstream src, arch, res;

		HuffmanArchiver a;
		HuffFileData x = a.archive(src, arch);

		HuffmanDearchiver d;
		HuffFileData y = d.dearchive(arch, res);

		CHECK(src.str().size() == x.input_sz);
		CHECK(arch.str().size() == x.output_sz + x.additional_sz);
		CHECK(x.input_sz == y.output_sz);
		CHECK(x.output_sz == y.input_sz);
		CHECK(x.additional_sz == y.additional_sz);
	}

	TEST_CASE("test 1-byte file statistics 2") {
		stringstream src, arch, res;
		src << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

		HuffmanArchiver a;
		HuffFileData x = a.archive(src, arch);

		HuffmanDearchiver d;
		HuffFileData y = d.dearchive(arch, res);

		CHECK(src.str().size() == x.input_sz);
		CHECK(arch.str().size() == x.output_sz + x.additional_sz);
		CHECK(x.input_sz == y.output_sz);
		CHECK(x.output_sz == y.input_sz);
		CHECK(x.additional_sz == y.additional_sz);
	}
	
}