cmake_minimum_required(VERSION 3.17)

project(FifteenPuzzle VERSION 1.0)

add_executable(fifteen_puzzle main.cpp)
target_include_directories(fifteen_puzzle PUBLIC include)
add_subdirectory(src)
target_link_libraries(fifteen_puzzle PRIVATE search)
add_compile_options(-Wall -pedantic -std=c++17)