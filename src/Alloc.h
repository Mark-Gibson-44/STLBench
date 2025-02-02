#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include <cassert>

namespace Benchstl
{

template <typename T>
class MemoryPoolAllocator
{
    struct Header
    {
        int _index;
        int _size;
        bool _used;
        Header(int index, int size) : _index(index), _size(size), _used(false){};
    };
public:
    MemoryPoolAllocator(size_t poolSize, uint16_t chunkSize) : _poolSize(poolSize), _chunkSize(chunkSize) 
    {
        _Memory = (T*)std::malloc(_poolSize);
        size_t numChunks = poolSize / chunkSize;
        for(size_t chunk = 0; chunk < numChunks; ++chunk)
        {
            // Use placement new
            Header add = {chunk, _chunkSize};
            _chunks.push_back(add);
        }

    };

    ~MemoryPoolAllocator()
    {
        // TODO FIX!!!
        _chunks.clear();
        //std::free(_Memory);
    }
    
    T* allocate(size_t size)
    {
        size_t numChunksNeeded = (sizeof(T) * size) / _chunkSize;
        if(numChunksNeeded > 1)
        {
            assert(true);
            // TODO, make a real check
            return nullptr;
        }
        auto unused_chunk = std::find_if(_chunks.begin(), _chunks.end(), [](const auto& node){ return node._used == false; });
        if(unused_chunk == _chunks.end())
        {
            return nullptr;
        }
        Header& chunk_to_use = *unused_chunk;
        chunk_to_use._used = true;
        T* alloc = (T*)&_Memory + chunk_to_use._index;
        //_chunks.erase(unused_chunk);
        return alloc;        
    }

    void deallocate(T* data, size_t size)
    {

    }
    void destroy(T* element);

    constexpr size_t max_size() const noexcept;
private:
    size_t _poolSize;
    uint16_t _chunkSize;
    std::vector<Header> _chunks;
    T* _Memory = nullptr;
};

template <typename T>
class FirstFit
{
    T* allocate(size_t size);
    void deallocate(T* data, size_t size);
    void destroy(T* element);

    constexpr size_t max_size() const noexcept;
};




} // Benchstl