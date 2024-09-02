cmake_minimum_required(VERSION 3.20)

set(T sort_bench)

project(${T})

add_executable(${T} main.cpp)

target_link_libraries(${T} benchmark::benchmark TBB::tbb)

target_include_directories(${T} PRIVATE ${CMAKE_SOURCE_DIR}/include)