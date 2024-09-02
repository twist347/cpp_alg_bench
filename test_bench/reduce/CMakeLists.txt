cmake_minimum_required(VERSION 3.20)

set(T reduce_bench)

project(${T})

#add_compile_options(-march=native -Ofast)

add_executable(${T} main.cpp)

target_link_libraries(${T} benchmark::benchmark TBB::tbb OpenMP::OpenMP_CXX)

target_include_directories(${T} PRIVATE ${CMAKE_SOURCE_DIR}/include)