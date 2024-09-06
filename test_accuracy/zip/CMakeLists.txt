cmake_minimum_required(VERSION 3.20)

set(T zip_accuracy)

project(${T})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,undefined")

add_executable(${T} main.cpp)

target_link_libraries(${T} gtest TBB::tbb OpenMP::OpenMP_CXX)

target_include_directories(${T} PRIVATE ${CMAKE_SOURCE_DIR}/include)