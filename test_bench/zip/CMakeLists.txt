cmake_minimum_required(VERSION 3.20)

set(T zip_bench)

project(${T})

add_executable(${T} main.cpp)

target_link_libraries(${T} benchmark::benchmark TBB::tbb OpenMP::OpenMP_CXX)

target_include_directories(${T} PRIVATE ${CMAKE_SOURCE_DIR}/include)