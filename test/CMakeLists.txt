

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
    )
    
    FetchContent_MakeAvailable(Catch2)
    
add_executable(unit_tests test_vec.cpp)
target_include_directories(unit_tests PRIVATE ../src)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_source_dir}/extras)
include(Catch)
catch_discover_tests(unit_tests)