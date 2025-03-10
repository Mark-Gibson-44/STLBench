#pragma once

#include <catch2/catch_test_macros.hpp>
#include <functional>
/*#include <iostream>
#include <type_traits>

template <typename T1, typename T2, typename Arg, typename ReturnType>
void checkMethodConsistency(ReturnType (T1::*method)(Arg), ReturnType (T2::*method2)(Arg), Arg arg) {
    // Ensure both T1 and T2 have the same method signature (same argument type and return type)
    static_assert(std::is_same_v<decltype((std::declval<T1>().*method)(arg)), ReturnType> &&
                  std::is_same_v<decltype((std::declval<T2>().*method2)(arg)), ReturnType>,
                  "Methods must have the same argument type and return type!");

    // Call the method for both types with the provided argument
    T1 obj1;
    T2 obj2;
    ReturnType result1 = (obj1.*method)(arg);
    ReturnType result2 = (obj2.*method2)(arg);

    std::cout << "Both methods returned the same type, and the argument was: " << arg << std::endl;
}
*/

// template <class... Types>
// void runFunc()

template <typename T>
void setup(T& single) {
  single.push_back(1);
}

template <typename T, typename... T2>
void setup(T& current, T2&... next) {
  current.push_back(1);
  setup(next...);
}

/*template <typename T, typename... T2>
void setup(T& current, T2&... next)
{
  current.push_back(1);
  setup(next...);
}*/

template <typename T>
void checkContents(int index, int expected, T& single) {
  REQUIRE(single[index] == expected);
}

template <typename T, typename... T2>
void checkContents(int index, int expected, T& current, T2&... next) {
  REQUIRE(current[index] == expected);
  checkContents(index, expected, next...);
}

template <typename T>
void runTest(T& vecType, std::function<void(T&)> func) {
  func(vecType);
}
