#pragma once

#include <cstdint>

// FUNCTIONS TO ADD
/*
    at
    operator[]
    front
    back
    data

    iterators(All of them)

    empty
    size
    max_size
    reserve
    capacity
    shrink_to_fit
    clear
    insert
    insert_range
    emplace
    erase
    push_back
    emplace_back
    append_range
    pop_back
    resize
    swap

*/
using TIndexType = uint16_t;


namespace Benchstl
{

template <typename T, typename Allocator>
class vector
{
private:
    TIndexType _capacity;
    TIndexType _size;
    Allocator _alloc;
    T* _data;
public:
    vector(uint16_t size, Allocator alloc) : _capacity(size + 2), _size(size), _alloc(alloc) {
        _data = _alloc.allocate(size);
    }
    vector(const vector& copy) noexcept;
    vector(vector&& mv) noexcept;
    vector operator=(const vector& copy) noexcept;
    vector operator=(vector&& mv) noexcept;
    ~vector() {
        delete _data;
    }

    const T& at(TIndexType index) const { return _data[index]; }
    const T& front() const { return _data[0]; }
    const T& back() const { return _data[_size - 1]; }
    void set(TIndexType index, T val) { _data[index] = val; }
    T& operator[](TIndexType index);

};


} // Benchstl