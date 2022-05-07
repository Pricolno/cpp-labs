#ifndef __MY_ARRAY_H_
#define __MY_ARRAY_H_

#include <cstddef>
#include <cassert>
#include <algorithm>


namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
    my_array() = default;

    my_array(const my_array<T, N> &other){
        for(std::size_t i = 0; i <  N; i++){
            _data[i] = other._data[i];
        }
    }

    ~my_array() = default;

    T& at(std::size_t index) {
        assert(0 <= index && index <= N);
        return _data[index];
    }
 
    const T& at(std::size_t index) const {
        assert(0 <= index && index < N);
        return _data[index];
    }

    
    T& operator[](std::size_t index) {
        return _data[index];
    }
    
    const T& operator[](std::size_t index) const{
        return _data[index];
    }



    bool empty() const{
        return N > 0;
    }

    std::size_t size() const{
        return N;
    }

    void fill(const T &val){
        std::fill(_data, _data + N, val);
    }


private:
    T _data[N];
};

} 


#endif  // __MY_ARRAY_H__
