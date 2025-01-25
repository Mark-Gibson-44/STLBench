

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
    )
    
    FetchContent_MakeAvailable(Catch2)
    
function(AddCoverage target)
    find_program(LCOV_PATH lcov REQUIRED)
    find_program(GENHTML_PATH genhtml REQUIRED)
    add_custom_target(coverage
        COMMENT "Running coverage for ${target}..."
        COMMAND ${LCOV_PATH} -d . --zerocounters
        COMMAND $<TARGET_FILE:${target}>
        COMMAND ${LCOV_PATH} -d . --capture -o coverage.info
        COMMAND ${LCOV_PATH} -r coverage.info '/usr/include/*'
                             -o filtered.info
        COMMAND ${GENHTML_PATH} -o coverage filtered.info
        --legend
        COMMAND rm -rf coverage.info filtered.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}   
    )
endfunction()

add_executable(unit_tests test_vec.cpp)
set_property(TARGET unit_tests PROPERTY CXX_STANDARD 23)
target_include_directories(unit_tests PRIVATE ../src)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    message("Generating coverage")
    target_compile_options(unit_tests PRIVATE --coverage)
    target_link_options(unit_tests PUBLIC --coverage)
    add_custom_command(TARGET unit_tests PRE_BUILD COMMAND
                        find ${CMAKE_BINARY_DIR} -type f
                        -name '*.gcda' -exec rm {} +)
endif()           
AddCoverage(unit_tests)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_source_dir}/extras)
include(Catch)
catch_discover_tests(unit_tests)