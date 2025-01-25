#pragma once

#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>

// FUNCTIONS TO ADD
/*


    iterators(All of them)

    max_size
    shrink_to_fit
    insert
    insert_range
    emplace
    erase
    emplace_back
    append_range
    resize
    swap

*/
using TIndexType = uint16_t;

namespace Benchstl {

template <typename T, typename Allocator>
class vector {
 private:
  static constexpr TIndexType _capacityBuffer = 2;
  static constexpr TIndexType _maxCapacity = std::numeric_limits<TIndexType>::max();
  TIndexType _capacity;
  TIndexType _size;
  Allocator _alloc;
  T* _data;

 public:
  static TIndexType maxCapacity() { return _maxCapacity; }

  vector(uint16_t size, Allocator alloc) noexcept : _capacity(size + _capacityBuffer), _size(size), _alloc(alloc) {
    _data = _alloc.allocate(_capacity);
  }

  vector(const vector& copy) noexcept : _alloc(copy._alloc), _capacity(copy._capacity), _size(copy._size) {
    _data = _alloc.allocate(_capacity);
    _populate(copy);
  }

  vector(vector&& mv) noexcept;
  vector operator=(const vector& copy) noexcept;
  vector operator=(vector&& mv) noexcept;
  ~vector() noexcept {
    if(_capacity){
      delete _data;
    }  
  }

  const T& at(TIndexType index) const { return _data[index]; }
  const T& front() const { return _data[0]; }
  const T& back() const { return _data[_size - 1]; }
  TIndexType size() const noexcept { return _size; }
  TIndexType capacity() const noexcept { return _capacity; }
  bool empty() const noexcept { return _size == 0; }

  T* data() const { return _data; }

  void set(TIndexType index, T val) { _data[index] = val; }
  T& operator[](TIndexType index) { return _data[index]; }

  void push_back(T val) {
    if (_size < _capacity) {
      _data[_size] = val;
      ++_size;
    } else {
      // Re alloc
      T* newAlloc = _alloc.allocate(_capacity + _capacityBuffer);
      std::memcpy(newAlloc, _data, sizeof(T) * _capacity);
      delete _data;
      _data = newAlloc;
      ++_size;
      _capacity += _capacityBuffer;
    }
  }

  void clear()
  {
    delete _data;
    _size = 0;
    _capacity = 0;
  }

  void reserve(TIndexType size)
  {
    if(size > this->_capacity)
    {
      T* newAlloc = _alloc.allocate(size);
      std::memcpy(newAlloc, _data, sizeof(T) * _capacity);
      delete _data;
      _data = newAlloc;
      _capacity = size;
    }
  }

  void pop_back() {
    _alloc.destroy(_data[_size]);
    --_size;
  }

 private:
  void _populate(const vector<T, Allocator>& data) {
    for (TIndexType insertIndex = 0; insertIndex < data._size; ++insertIndex) {
      _data[insertIndex] = data.at(insertIndex);
    }
  }
};

template <typename T, typename Allocator>
class smallVector
{
 private:
  static constexpr TIndexType _capacityBuffer = 2;
  static constexpr TIndexType _maxCapacity = std::numeric_limits<TIndexType>::max();
  TIndexType _capacity;
  TIndexType _size;
  Allocator _alloc;
  union{
    T* _data;
    T* _smallData;
  };

};
}  // namespace Benchstl