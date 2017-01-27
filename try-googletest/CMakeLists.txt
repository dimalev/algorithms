cmake_minimum_required(VERSION 2.8.2)
project(test-googletest)
add_subdirectory(${CMAKE_BINARY_DIR}/googletest)

add_executable(example example.cpp)
target_link_libraries(example gtest_main)
include(CTest)
add_test(NAME example_test COMMAND example)
