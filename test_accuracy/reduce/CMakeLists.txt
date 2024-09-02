cmake_minimum_required(VERSION 3.20)

set(T reduce_accuracy)

project(${T})

add_executable(${T} main.cpp)

target_link_libraries(${T} gtest TBB::tbb OpenMP::OpenMP_CXX)

target_include_directories(${T} PRIVATE ${CMAKE_SOURCE_DIR}/include)