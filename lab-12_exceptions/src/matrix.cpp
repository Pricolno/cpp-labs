#include "matrix.hpp"

#include <fstream>
#include <cstring>
#include <algorithm>
#include <string>


MatrixException::MatrixException(const std::string &msg): std::invalid_argument(msg) {}

Matrix::Matrix() {
	_rows = 0; _cols = 0;
}

void Matrix::reserve(std::size_t r, std::size_t c){
	_data = new int[r * c];
	_ptr = new int*[r];

	for (std::size_t i = 0; i < r; i++) {
		_ptr[i] = _data + i * c;
	}
}

Matrix::Matrix(std::size_t r, std::size_t c) {
	_rows = r; _cols = c;
	reserve(_rows, _cols);
	std::fill(_data, _data + r * c, 0);
}

Matrix::Matrix(const Matrix &m) {
	_rows = m._rows; _cols = m._cols;
	reserve(_rows, _cols);
	std::memcpy(_data, m._data, _rows * _cols * sizeof(int));
}

Matrix::~Matrix() {
	delete[] _data;
	delete[] _ptr;
}

int Matrix::get(std::size_t i, std::size_t j) const {
	if (i >= _rows || j >= _cols) {
		throw MatrixException("bad index");
	}

	return _ptr[i][j];
}

void Matrix::load(std::ifstream &in) {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			in >> _ptr[i][j];
		}
	}

	if (!in) {
		throw MatrixException("invalid file format");
	}
}


Matrix* Matrix::load_matrix_from_file(const std::string &fname) {
	std::ifstream in(fname);
	if (!in) {
		throw MatrixException("unable to open file");
	}

	std::size_t r, c;
	in >> r >> c;
	if (!in) {
		throw MatrixException("invalid file format");
	}

	Matrix *m = new Matrix(r, c);
	try {
		m->load(in);
	} catch (MatrixException &e) {
		delete m;
		throw e;
	}

	return m;
}


void Matrix::print(std::ostream &out) const{
	for (std::size_t i = 0; i < _rows; i++){
		for (std::size_t j = 0; j < _cols - 1; j++){
			out << _ptr[i][j] << " ";
		}
		out << _ptr[i][_cols - 1] << "\n";
	}

}


Matrix& Matrix::operator=(Matrix m){
	std::swap(_rows, m._rows);
	std::swap(_cols, m._cols);
	std::swap(_data, m._data);
	std::swap(_ptr, m._ptr);

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (_rows != m._rows || _cols != m._cols) {
		throw MatrixException("dimensions do not match");
	}

	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			_ptr[i][j] += m._ptr[i][j];
		}
	}
	return *this;
}


Matrix& Matrix::operator*=(const Matrix& m) {
	if (_rows != m._cols) {
		throw MatrixException("#arg1.columns != #arg2.rows");
	}

	Matrix result(_rows, m._cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < m._cols; j++) {
			for (std::size_t k = 0; k < _cols; k++) {
				result._ptr[i][j] += _ptr[i][k] * m._ptr[k][j];
			}
		}
	}
	*this = result;
	return *this;
}




