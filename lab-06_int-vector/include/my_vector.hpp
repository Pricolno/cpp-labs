#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#include <cstddef>

class MyVector {
public:
    MyVector();
    MyVector(std::size_t init_capacity);
    ~MyVector();

    void set(std::size_t index, int value);
    int get(std::size_t index);

    std::size_t size() const;
    std::size_t capacity() const;

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);

    void push_back(int value);
    void insert(std::size_t index, int value);
    void erase(std::size_t index);

    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    //MyVector& operator=(const MyVector& other);

    void swap(MyVector &other);

private:
    std::size_t _size = 0, _capacity = 0;
    int * _data = nullptr;

};

#endif
