#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "vec.h"

// Testing alternate implementations of Vector

TEST_CASE("Basic Test", "[SETUP]") {
  Benchstl::vector<int, std::allocator<int>> test(10, std::allocator<int>());

  test.set(0, 4);

  test[3] = 2;
  REQUIRE(test.at(0) == 4);
  REQUIRE(test.at(3) == 2);
}

TEST_CASE("Test copy construction", "[SETUP]") {
  Benchstl::vector<int, std::allocator<int>> test(10, std::allocator<int>());
  for (uint16_t index = 0; index < 10; ++index) {
    test.set(index, index);
  }
  Benchstl::vector<int, std::allocator<int>> copy(test);

  for (uint16_t index = 0; index < 10; ++index) {
    REQUIRE(test.at(index) == copy.at(index));
  }
}

TEST_CASE("Test Pushback", "[SETUP]") {
  Benchstl::vector<int, std::allocator<int>> test(2, std::allocator<int>());
  for (int i = 0; i < 10; ++i) {
    test.push_back(i);
  }
  REQUIRE(test.size() == 12);
}
