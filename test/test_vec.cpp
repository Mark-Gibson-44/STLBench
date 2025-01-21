
#include <catch2/catch_test_macros.hpp>

#include "vec.h"
#include <vector>

// Testing alternate implementations of Vector


TEST_CASE("Basic Test", "[SETUP]")
{
    Benchstl::vector<int, std::allocator<int>> test(10, std::allocator<int>());

    test.set(0, 4);
    REQUIRE(test.at(0) == 4);    
}
