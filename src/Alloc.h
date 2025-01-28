#pragma once
#include <cstdint>


namespace Benchstl
{

template <typename T>
class MemoryPoolAllocator
{
    MemoryPoolAllocator(uint16_t poolSize, uint16_t chunkSize);
    T* allocate(size_t size);
    voi deallocate(T* data, size_t size);
    void destroy(T* element);

    constexpr size_t max_size() const noexcept;

    size_t _poolSize;
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