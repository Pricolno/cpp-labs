#include "bitio.h"
#include <iostream>
#include <cassert>
#include <climits>

namespace bit_io {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BitInputStream::BitInputStream(std::istream &_in): in(_in) {
	update_buffer();
}

BitInputStream::~BitInputStream() {}

bool BitInputStream::read_bit() {
	assert(buf_pos <= CHAR_BIT);
	if (buf_pos == CHAR_BIT) {
		update_buffer();
	}
	bool result = buffer & bit_mask;
	bit_mask <<= 1; buf_pos++;
	return result;
}

void BitInputStream::update_buffer() {
	if (!in.read(&buffer, 1)) {
		throw std::istream::failure("no bits left in input");
	}
	bit_mask = 1; buf_pos = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BitOutputStream::BitOutputStream(std::ostream &_out): out(_out), buffer(0), bit_mask(1), buf_pos(0) {}

BitOutputStream::~BitOutputStream() {
	release_buffer();
}

void BitOutputStream::write_bit(bool bit) {
	assert(buf_pos <= CHAR_BIT);
	if (buf_pos == CHAR_BIT) {
		release_buffer();
	}
	if (bit) {
		buffer |= bit_mask;
	}
	bit_mask <<= 1; buf_pos++;
}

void BitOutputStream::release_buffer() {
	if (!buf_pos) {
		return;
	}
	out.write(&buffer, 1);
	bit_mask = 1; buf_pos = 0; buffer = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}