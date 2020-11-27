cmake_minimum_required(VERSION 3.10)

project(FifteenPuzzle VERSION 1.0)

add_executable(eight_puzzle main.cpp)
target_include_directories(eight_puzzle PUBLIC include)
add_subdirectory(src)
target_link_libraries(eight_puzzle PRIVATE search)
add_compile_options(-Wall -pedantic -std=c++17)
