#include <vector>

#include "test_setup.h"
#include "vec.h"

// Testing alternate implementations of Vector

TEST_CASE("Basic Test", "[SETUP]") {
  Benchstl::vector<int, std::allocator<int>> test(10, std::allocator<int>());

  test.set(0, 4);

  test[3] = 2;
  REQUIRE(test.at(0) == 4);
  REQUIRE(test.at(3) == 2);
}

TEST_CASE("Basic small vec Test", "[SETUP]") {
  Benchstl::smallVector<int, std::allocator<int>> test(4, std::allocator<int>());

  test[3] = 2;
  REQUIRE(test.at(3) == 2);
  REQUIRE(test[3] == 2);

  Benchstl::smallVector<int, std::allocator<int>> test2(10, std::allocator<int>());
  test2[3] = 2;
  REQUIRE(test2.at(3) == 2);
  REQUIRE(test2[3] == 2);
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

TEST_CASE("Test Clear", "[SETUP]") {
  Benchstl::vector<int, std::allocator<int>> test(2, std::allocator<int>());
  for (int i = 0; i < 10; ++i) {
    test.push_back(i);
  }

  test.clear();
  REQUIRE(test.size() == 0);
}

template <typename T>
static constexpr void push_backN(T& vec) {
  for (int i = 0; i < 3; i++) {
    vec.push_back(i);
  }
}

TEST_CASE("Test setup func", "[SETUP]") {
  Benchstl::vector<int, std::allocator<int>> testVec(0, std::allocator<int>());
  std::vector<int> testRealVec(0);

  // TODO, wrap calling runTest for each type with some sort of parameter packing
  runTest(testVec, push_backN<decltype(testVec)&>);
  runTest(testRealVec, push_backN<decltype(testRealVec)&>);
  REQUIRE(testVec.size() == 3);
  REQUIRE(testRealVec.size() == 3);
}

TEST_CASE("Test push_back pack expansion", "[SETUP]") {
  Benchstl::vector<int, std::allocator<int>> bare(0, std::allocator<int>());
  Benchstl::smallVector<int, std::allocator<int>> small(0, std::allocator<int>());
  std::vector<int> standard(0);

  setup(bare, small, standard);
  checkContents(0, 1, bare, small, standard);
}
