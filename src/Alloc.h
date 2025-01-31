#pragma once
#include <cstdint>
#include <memory>
#include <list>

namespace Benchstl
{

template <typename T>
class MemoryPoolAllocator
{
    struct Header
    {
        int _size;
        bool _used;
        Header(int size) _size(size), _used(false){};
    };

    MemoryPoolAllocator(size_t poolSize, uint16_t chunkSize) : _poolSize(poolSize), _chunkSize(chunkSize) 
    {
        _Memory = std::malloc(_poolSize);
        size_t numChunks = poolSize / chunkSize;
        for(size_t chunk = 0; chunk < numChunks; ++chunk)
        {
            // Use placement new
            _chunks.insert(_chunkSize);
        }

    };
    T* allocate(size_t size)
    {
        size_t numChunksNeeded = (sizeof(T) * size) / _chunkSize;

        
    }
    void deallocate(T* data, size_t size);
    void destroy(T* element);

    constexpr size_t max_size() const noexcept;

    size_t _poolSize;
    uint16_t _chunkSize;
    std::list<Header> _chunks;
    void* _Memory = nullptr;
};

template <typename T>
class FirstFit
{
    T* allocate(size_t size);
    voi deallocate(T* data, size_t size);
    void destroy(T* element);

    constexpr size_t max_size() const noexcept;
};




} // Benchstl