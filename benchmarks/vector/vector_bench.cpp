#include <iostream>
#include <chrono>
#include <cstdint>
#include <vector>

#include "vec.h"
// Todo, think about how to mess with system calls for better affinity
int main()
{
    
    const std::chrono::time_point<std::chrono::high_resolution_clock> start =
        std::chrono::high_resolution_clock::now();

    std::vector<uint64_t> test;
    constexpr uint64_t loopNum = 0x7FFFFFF;
    test.reserve(loopNum);
    for(uint64_t i = 1; i < loopNum; i++)
    {
        test.push_back(i);
    }
    
    const std::chrono::time_point<std::chrono::high_resolution_clock> Finish1 =
        std::chrono::high_resolution_clock::now();

    const std::chrono::time_point<std::chrono::high_resolution_clock> Start2 =
        std::chrono::high_resolution_clock::now();

    Benchstl::vector<uint64_t, std::allocator<uint64_t>> test2(0, std::allocator<uint64_t>());
    test2.reserve(loopNum);
    
    for(uint64_t i = 1; i < loopNum; i++)
    {
        test2.push_back(i);
    }
    
    const std::chrono::time_point<std::chrono::high_resolution_clock> Finish2 =
        std::chrono::high_resolution_clock::now();
    


    double std_elapsed_time_ms = std::chrono::duration<double, std::milli>(Finish1-start).count();
    double impl_elapsed_time_ms = std::chrono::duration<double, std::milli>(Finish2 - Start2).count();

    std::cout << "STD " << std_elapsed_time_ms << " Vec size " << test.size() << '\n';
    std::cout << "IMPL " << impl_elapsed_time_ms <<  " Vec size " << test2.size() << '\n';
    return 0;

}