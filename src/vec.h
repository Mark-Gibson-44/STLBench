#pragma once

#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>
#include <memory>

// FUNCTIONS TO ADD
/*


    iterators(All of them)

    insert
    insert_range
    emplace
    erase
    emplace_back
    append_range
    resize
    swap

*/
using TIndexType = uint64_t;

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
    static_assert(!std::is_same<T, std::string>::value);
    if (_size < _capacity) {

      _data[_size] = val;
    } else {
      // Re alloc
      T* newAlloc = _alloc.allocate(_capacity + _capacityBuffer);
      std::memcpy(newAlloc, _data, sizeof(T) * _capacity);
      delete _data;
      _data = newAlloc;
      _data[_size] = val;
      _capacity += _capacityBuffer;
    }
    ++_size;
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

  void resize(TIndexType count)
  {
    if(_size != count)
    {
      if(_size > count)
      {
        for(TIndexType removed = _size - 1; removed > count; --removed)
        {
          _alloc.destroy(_data[removed]);
        }
      }
      else
      {
        if(_capacity < count)
        {
          reserve(count);
        }
      }
      _size = count;
    }

  }

  void resize(TIndexType count, const T& value/* = T()??*/)
  {

  }

  void shrink_to_fit()
  {
    T* newAlloc = _alloc.allocate(_size);
    std::memcpy(newAlloc, _data, sizeof(T) * _size);
    delete _data;
    _data = newAlloc;
    _capacity = _size;
  }

  void pop_back() {
    _alloc.destroy(_data[_size]);
    --_size;
  }

  template<class... Args>
  void emplace_back(Args&&... args)
  {
    if(_size == _capacity)
    {
      T* newAlloc = _alloc.allocate(_capacity + _capacityBuffer);
      std::memcpy(newAlloc, _data, sizeof(T) * _capacity);
      delete _data;
      _data = newAlloc;
      _capacity += _capacityBuffer;
    }
    // Understand this better
    //std::construct_at(_data[_size], std::forward<Args>(args)...);
    ++_size;
  }

  bool operator== (const std::vector<T>& rhs) const
  {
    return rhs.size() == this->size() && compareContents(rhs);
  }

 private:
  void _populate(const vector<T, Allocator>& data) {
    for (TIndexType insertIndex = 0; insertIndex < data._size; ++insertIndex) {
      _data[insertIndex] = data.at(insertIndex);
    }
  }

  bool compareContents(const std::vector<T>& vec) const
  {
    for(TIndexType index = 0; index < this->size(); ++index)
    {
      if(vec.at(index) != this->at(index))
      {
        return false;
      }
    }
    return true;
  }
};

template <typename T, typename Allocator>
class smallVector
{
 private:
  static constexpr TIndexType _smallVectorSize = 8;
  static constexpr TIndexType _capacityBuffer = 2;
  static constexpr TIndexType _maxCapacity = std::numeric_limits<TIndexType>::max();
  TIndexType _capacity;
  TIndexType _size;
  Allocator _alloc;
  union TData{
    T* _bigData;
    T* _smallData[_smallVectorSize];
  };
  TData _data;

public:
  smallVector(uint16_t size, Allocator alloc) noexcept : _capacity(size), _size(size), _alloc(alloc) {
    if(_capacity > _smallVectorSize)
    {
      _data._bigData = _alloc.allocate(_capacity);
    }
    else
    {
      _capacity = _smallVectorSize;
    }
  }
  ~smallVector() noexcept {
    if(_capacity > _smallVectorSize){
      delete _data._bigData;
    }  
  }

  const T& at(TIndexType index) const { return _GetData()[index]; }
  const T& front() const { return _GetData()[0]; }
  const T& back() const { return _GetData()[_size - 1]; }
  TIndexType size() const noexcept { return _size; }
  TIndexType capacity() const noexcept { return _capacity; }
  bool empty() const noexcept { return _size == 0; }
  T& operator[](TIndexType index) { return _GetData()[index]; }


  void push_back(T val) {
    if (_size < _capacity) {
      _GetData()[_size] = val;
      ++_size;
    } else {
      // Re alloc
      T* newAlloc = _alloc.allocate(_capacity + _capacityBuffer);
      std::memcpy(newAlloc, _GetData(), sizeof(T) * _capacity);
      delete _GetData();
      _data._bigData = newAlloc;
      ++_size;
      _capacity += _capacityBuffer;
    }
  }

private:
  T* _GetData() const
  {
    return _capacity > _smallVectorSize ? _data._bigData : (T*)_data._smallData;
  }
};
}  // namespace Benchstl