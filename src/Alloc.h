#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

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
        Header* next = nullptr;
        void insert(Header* node)
        {
            auto* iter = this;

            while(iter->next != nullptr)
            {
                iter = iter->next;
            }
            iter->next = node;
        }
        std::optional<Header*> findFree()
        {
            Header* iter = this;
            while(iter != nullptr)
            {
                if(!iter->_used)
                {
                    return iter;
                }
            }
            return std::nullopt;
        }
        void erase(Header* node)
        {
            Header* iter = this;
            while(iter != nullptr && iter->next != node)
            {
                iter = iter->next;
            }
            if(iter == nullptr)
            {
                assert(true);
            }
            iter->next = iter->next->next;
        }

        Header(int index, int size) : _index(index), _size(size), _used(false), next(nullptr){};
    };
public:
    MemoryPoolAllocator(size_t poolSize, uint16_t chunkSize) : _poolSize(poolSize), _chunkSize(chunkSize) 
    {
        _Memory = (T*)std::malloc(_poolSize);
        size_t numChunks = poolSize / chunkSize;
        for(size_t chunk = 0; chunk < numChunks; ++chunk)
        {
            void* offset = (void*)(uintptr_t(_Memory) + (chunk * sizeof(Header)));
            // Use placement new
            Header* node = new(offset) Header{chunk, _chunkSize}; 
            if(this->_freeChunksHead == nullptr)
            {
                this->_freeChunksHead = node;
            }
            else
            {
                this->_freeChunksHead->insert(node);
            }
        }

    };
    MemoryPoolAllocator(const MemoryPoolAllocator& cp) = delete;
    MemoryPoolAllocator(MemoryPoolAllocator&& mv)
    {
        _Memory = mv._Memory;
        mv._Memory = nullptr;
        this->_freeChunksHead = std::move(mv._freeChunksHead);
        this->_poolSize = mv._poolSize;
        this->_chunkSize = mv._chunkSize;

    }

    ~MemoryPoolAllocator()
    {
        std::free(_Memory);
    }
    
    T* allocate(size_t size)
    {
        size_t numChunksNeeded = (sizeof(T) * size) / _chunkSize;
        if(numChunksNeeded > 1)
        {
            assert(false);
            // TODO, make a real check
            return nullptr;
        }

        auto opt_unused_chunk = _freeChunksHead->findFree();
        if(!opt_unused_chunk.has_value())
        {
            return nullptr;
        }

        Header* node = opt_unused_chunk.value();
        node->_used = true;
        T* alloc = (T*)(uintptr_t(node) + sizeof(Header));
        if(node == _freeChunksHead)
        {
            _freeChunksHead = _freeChunksHead->next;
        }
        else
        {
            _freeChunksHead->erase(node);
        }
        return alloc;        
    }

    void deallocate(T* data, size_t size)
    {
        Header* node = (Header*)(uintptr_t(data)/* - sizeof(Header)*/);
        node->_used = false;
        _freeChunksHead->insert(node);
    }
    void destroy(T* element);
    size_t poolSize() const { return _poolSize; };
    constexpr size_t max_size() const noexcept;
private:
    size_t _poolSize;
    uint16_t _chunkSize;
    Header* _freeChunksHead = nullptr;
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