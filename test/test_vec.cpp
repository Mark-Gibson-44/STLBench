#include <string>
#include <vector>

#include "Alloc.h"
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

TEST_CASE("Test Alloc", "[SETUP]") {
  Benchstl::vector<int, Benchstl::MemoryPoolAllocator<int>> test(2, Benchstl::MemoryPoolAllocator<int>(128, 32));
  REQUIRE(test.size() == 2);
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

// TODO investigate string allocation issues
TEST_CASE("Test non-int type vectors") {
  struct testType {
    char a;
    char b;

    bool operator==(testType rhs) const { return rhs.a == a && rhs.b == b; }
  };
  Benchstl::vector<testType, std::allocator<testType>> bare(0, std::allocator<testType>());
  std::vector<testType> stl;
  char front = 'a';
  char back = 'z';
  testType input;
  for (uint16_t charNum = 0; charNum < 25; ++charNum) {
    input.a = front + charNum;
    input.b = back - charNum;
    bare.push_back(input);
    stl.push_back(input);
  }
  REQUIRE(bare == stl);
}

// TODO fix for strings
/*TEST_CASE("Test string type vectors") {
  std::vector<std::string> s;
  Benchstl::vector<std::string, std::allocator<std::string>> s2(0, std::allocator<std::string>());

  std::string input = "a";
  for (int i = 0; i < 25; ++i) {
    input += input[i] + 1;
    s.push_back(input);
    s2.push_back(input);
  }
  REQUIRE(s == s2);
}*/

TEST_CASE("Test array type vectors") {
  int arr[4] = {1, 2, 3, 4};
  std::vector<int*> s;
  Benchstl::vector<int*, std::allocator<int*>> s2(0, std::allocator<int*>());

  for (int i = 0; i < 25; ++i) {
    s.push_back(arr);
    s2.push_back(arr);
  }

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 4; j++) {
      REQUIRE(s.at(i)[j] == s2.at(i)[j]);
    }
  }
}
