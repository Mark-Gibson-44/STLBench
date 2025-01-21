cmake_minimum_required(VERSION 3.22.0)

project(STL_TESTING CXX)
include(CTest)
add_subdirectory(src bin)
add_subdirectory(test)