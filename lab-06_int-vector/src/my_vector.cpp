#include "my_vector.hpp"

#include <cstdio>
#include <algorithm>
#include <cstring>

MyVector::MyVector(){
	reserve(2);
}

MyVector::MyVector(std::size_t init_capacity){
	reserve(init_capacity);
}

MyVector::~MyVector(){
	delete [] _data;
	_size = 0;
	_capacity = 0;
}

void MyVector::set(std::size_t index, int value){
	_data[index] = value;
}

 int MyVector::get(std::size_t index){
 	return _data[index];
 }

std::size_t MyVector::size() const{
	return _size;
}

std::size_t MyVector::capacity() const{
	return _capacity;
}

void MyVector::reserve(std::size_t new_capacity){
	if(_capacity >= new_capacity) 
		return;

	int* new_data = new int[new_capacity];
	std::copy_n(_data, _size, new_data);

	delete [] _data;
	_data = new_data;
	_capacity = new_capacity;
}

void MyVector::resize(std::size_t new_size){
	if(new_size <= _size){
		_size = new_size;
		return;
	}
	reserve(std::max(new_size, 2 * _capacity));
    std::fill(_data + _size, _data + new_size, 0);

    _size = new_size;
}

void MyVector::push_back(int value){
	if(_size == _capacity)
		reserve(2 * _capacity);

	_data[_size] = value;
	_size++;
}

void MyVector::insert(std::size_t index, int value){
	if (_size  == _capacity)
        reserve(2 * _capacity);
    
    memmove(_data + index + 1, _data + index, (_size - index) * sizeof(int));
    _data[index] = value;
   	_size++;
}

void MyVector::erase(std::size_t index){
	memmove(_data + index, _data + index + 1, (_size - index) * sizeof(int));
	_size--;
}

MyVector::MyVector(const MyVector& other) {
    _capacity = other._capacity;
    _size = other._size;
    memcpy(_data, other._data, size() * sizeof(int));
}

MyVector &MyVector::operator=(const MyVector &other){
    MyVector tmp(other);
    swap(tmp);
    return *this;
}

void MyVector::swap(MyVector &other) {
    std::swap(_data, other._data);
    std::swap(_capacity, other._capacity);
    std::swap(_size, other._size); 
}
