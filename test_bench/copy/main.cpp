#include <benchmark/benchmark.h>
#include <execution>

#include "utils.h"
#include "copy.h"

using value_type = int;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 1.0;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 250'000, finish = 1'000'000, step = 250'000;

constexpr auto time_unit = benchmark::kNanosecond;

static auto gb_naive_loop_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = copy::naive_loop_alg(std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_loop_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = copy::loop_alg(std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_openmp_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = copy::openmp_alg(std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::copy(std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::copy(std::execution::par, std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res = std::copy(std::execution::unseq, std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::copy(std::execution::par_unseq, std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_memcpy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_ptr = std::memcpy(std::data(to), std::data(from), std::size(to) * sizeof(value_type));

        benchmark::DoNotOptimize(res_ptr);
        benchmark::ClobberMemory();
    }
}

constexpr std::size_t iter_num = 1000;

BENCHMARK(gb_naive_loop_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_loop_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_openmp_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_copy_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_copy_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_copy_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_memcpy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);

BENCHMARK_MAIN();