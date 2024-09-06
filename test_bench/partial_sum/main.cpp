#include <benchmark/benchmark.h>
#include <numeric>
#include <execution>

#include "utils.h"
#include "partial_sum.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 1.0;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 2'500'000, finish = 10'000'000, step = 2'500'000;

constexpr auto time_unit = benchmark::kMicrosecond;

static auto gb_naive_par_sum_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = par_sum::naive_partial_sum(std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_par_sum_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = par_sum::naive_partial_sum(std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::inclusive_scan(std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::inclusive_scan(std::execution::par, std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::inclusive_scan(std::execution::unseq, std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::inclusive_scan(std::execution::par_unseq, std::cbegin(from), std::cbegin(from), std::begin(to));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

constexpr std::size_t iter_num = 100;

BENCHMARK(gb_naive_par_sum_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_par_sum_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_inc_scan_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_inc_scan_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_inc_scan_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_std_inc_scan_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);

BENCHMARK_MAIN();