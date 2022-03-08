#include "matrix.h"

#include <algorithm>
#include <cstring>
#include <stdio.h>

Matrix::Matrix(std::size_t r, std::size_t c) : _rows(r), _cols(c) {
    _data = alloc_2d_array(r, c);

}

Matrix::Matrix() {
    _data = nullptr;
    _rows = 0, _cols = 0;
}

Matrix::~Matrix() {
    delete [] _data;
}

Matrix& Matrix::operator=(const Matrix &other) {
    if (this == &other)
        return *this;

    if (_rows != other._rows || _cols != other._cols) {
        delete [] _data;
        _data = alloc_2d_array(other._rows, other._cols);
    }

    memcpy(_data[0], other._data[0], other._rows * other._cols * sizeof(int));
    _rows = other._rows;
    _cols = other._cols;

    return *this;
}

Matrix::Matrix(const Matrix &other) {
    if (_data == nullptr) {
        _rows = 0, _cols = 0;
    }
    *this = other;
}


std::size_t Matrix::get_rows() { return _rows; }
std::size_t Matrix::get_cols() { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return (int)_data[i][j];
}

void Matrix::print(FILE* f) {
    //fprintf(f, "\n");
    for (size_t r = 0; r < _rows; ++r) {
        for (size_t c = 0; c < _cols; ++c) {
            if (c != 0) fprintf(f, " %d",_data[r][c]);
            else fprintf(f, "%d",_data[r][c]);
        }
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(Matrix& m) const{
    if(_rows != m._rows || _cols != m._cols) return false;
    for(size_t r = 0; r < _rows; r++){
        for(size_t c = 0; c < _cols; c++){
            if(_data[r][c] != m._data[r][c]) return false;
        }
    }
    return true;
}

bool Matrix::operator!=(Matrix& m) const{
  return !(*this == m);
}

Matrix& Matrix::operator+=(Matrix& m) {
    for(std::size_t r = 0; r < _rows; r++){
        for(std::size_t c = 0; c < _cols; c++){
            _data[r][c] += m._data[r][c];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(Matrix& m) {
    for(std::size_t r = 0; r < _rows; r++){
        for(std::size_t c = 0; c < _cols; c++){
            _data[r][c] -= m._data[r][c];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(Matrix& m) {
    return *this = *this * m;
}

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c(a._rows, b._cols);
    for (std::size_t i = 0; i < a._rows; ++i)
        for (std::size_t j = 0; j < b._cols; ++j)
            for (std::size_t k = 0; k < a._cols; ++k)
                c._data[i][j] += a._data[i][k] * b._data[k][j];
    return c;
}

Matrix Matrix::operator+(Matrix& m) {
    Matrix other(m);
    return other += *this;
}

Matrix Matrix::operator-(Matrix& m) {
    Matrix other(m);
    other *= -1;
    return  other += *this;
}

int **Matrix::alloc_2d_array(std::size_t r, std::size_t c) {
    if (r == 0 || c == 0)
        return nullptr;

    char *raw = (char *) new int[r * sizeof(int*) + r * c * sizeof(int)];
    int *data = (int *) (raw + r * sizeof(int *));
    std::fill_n(data, r * c, 0);

    int **pointers = (int **)raw;
    for (std::size_t i = 0; i < r; ++i)
        pointers[i] = data + i * c;
    return pointers;
}

void Matrix::swap(Matrix &other){
    std::swap(_data, other._data);
    std::swap(_rows, other._rows);
    std::swap(_cols, other._cols);
}

Matrix& operator*=(Matrix &a, int val) {
    for (size_t i = 0; i < a._rows; ++i) {
        for (size_t j = 0; j < a._cols; ++j) {
            a._data[i][j] *= val;
        }
    }
    return a;
}



