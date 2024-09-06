#include <benchmark/benchmark.h>
#include <execution>

#include "utils.h"
#include "copy.h"

using value_type = int;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 1.0;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 25'000'000, finish = 100'000'000, step = 25'000'000;

constexpr auto time_unit = benchmark::kNanosecond;

static auto gb_naive_loop_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = copy::naive_loop_alg(std::cbegin(src), std::cbegin(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_loop_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = copy::loop_alg(std::cbegin(src), std::cbegin(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_openmp_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = copy::openmp_alg(std::cbegin(src), std::cbegin(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::copy(std::cbegin(src), std::cbegin(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::copy(std::execution::par, std::cbegin(src), std::cbegin(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::copy(std::execution::unseq, std::cbegin(src), std::cbegin(src), std::begin(dst));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::copy(std::execution::par_unseq, std::cbegin(src), std::cbegin(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_memcpy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_ptr = std::memcpy(std::data(dst), std::data(src), size * sizeof(value_type));

        benchmark::DoNotOptimize(res_ptr);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(gb_naive_loop_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit);
BENCHMARK(gb_loop_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit);
BENCHMARK(gb_openmp_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit);
BENCHMARK(gb_std_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit);
BENCHMARK(gb_std_copy_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit);
BENCHMARK(gb_std_copy_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit);
BENCHMARK(gb_std_copy_par_unseq_alg_bench)->DenseRange(start, finish, step);
BENCHMARK(gb_memcpy_alg_bench)->DenseRange(start, finish, step);

BENCHMARK_MAIN();