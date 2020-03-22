file(GLOB search_src *.cpp)
add_library(search STATIC ${search_src})
target_include_directories(search PRIVATE ../include)