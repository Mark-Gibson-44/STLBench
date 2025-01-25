cmake_minimum_required(VERSION 3.22.0)

project(STL_TESTING CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CTest)
add_subdirectory(src bin)
add_subdirectory(test)