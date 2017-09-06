cmake_minimum_required (VERSION 2.6)
project (BreakAESCBC)
add_executable(main main.cpp)
target_link_libraries(main curl)
