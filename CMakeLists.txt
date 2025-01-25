cmake_minimum_required(VERSION 3.22.0)

project(STL_TESTING CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#SET(CMAKE_CXX_CLANG_TIDY /usr/bin/clang-tidy;--checks=*;--warnings-as-errors=*)
#set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

#add_compile_options(-Wall -Wextra -Wpedantic)


include(CTest)
add_subdirectory(src bin)
add_subdirectory(test)