#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
    Matrix();

    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix &other);

    ~Matrix();

    Matrix& operator=(const Matrix &other);

    std::size_t get_rows();
    std::size_t get_cols();
    void set(std::size_t i, std::size_t j, int val);
    int get(std::size_t i, std::size_t j) const;
    void print(FILE *f);

    Matrix operator+(Matrix& m);
    Matrix operator-(Matrix& m);
    //Matrix operator*(Matrix& m);

    Matrix& operator+=(Matrix& m);
    Matrix& operator-=(Matrix& m);
    Matrix& operator*=(Matrix& m);

    bool operator==(Matrix& m) const;
    bool operator!=(Matrix& m) const;

    friend Matrix operator*(const Matrix &a, const Matrix &b);
    friend Matrix& operator*=(Matrix &a, int val);

    void swap(Matrix &other);

private:
    int** alloc_2d_array(std::size_t r, std::size_t c);
    std::size_t _rows = 0;
    std::size_t _cols = 0;
    int **_data = nullptr;
};

#endif
