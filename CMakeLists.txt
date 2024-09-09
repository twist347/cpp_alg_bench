cmake_minimum_required(VERSION 3.20)

set(T cpp_alg_bench)

project(${T})

find_package(TBB REQUIRED)
find_package(OpenMP REQUIRED)
find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(test_bench_path ${CMAKE_SOURCE_DIR}/test_bench)
set(test_accuracy_path ${CMAKE_SOURCE_DIR}/test_accuracy)

add_executable(${T} main.cpp)

# bench tests
add_subdirectory(${test_bench_path}/reduce)
add_subdirectory(${test_bench_path}/sort)
add_subdirectory(${test_bench_path}/sort_quiz)
add_subdirectory(${test_bench_path}/map)
add_subdirectory(${test_bench_path}/zip)
add_subdirectory(${test_bench_path}/copy/copy_nums)
add_subdirectory(${test_bench_path}/copy/copy_strings)
add_subdirectory(${test_bench_path}/partial_sum)

# accuracy tests
add_subdirectory(${test_accuracy_path}/copy)
add_subdirectory(${test_accuracy_path}/reduce)
add_subdirectory(${test_accuracy_path}/map)
add_subdirectory(${test_accuracy_path}/zip)
add_subdirectory(${test_accuracy_path}/partial_sum)