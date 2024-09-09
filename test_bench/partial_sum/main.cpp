#include <benchmark/benchmark.h>
#include <numeric>
#include <execution>

#include "utils.h"
#include "partial_sum.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 1.0;
constexpr value_type min_val = 0.0;

constexpr std::size_t start = 2'500'000, finish = 10'000'000, step = 2'500'000;

constexpr auto time_unit = benchmark::kMicrosecond;

static auto gb_naive_p_sum_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = par_sum::naive_partial_sum(std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_p_sum_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = par_sum::naive_partial_sum(std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::inclusive_scan(std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::inclusive_scan(std::execution::par, std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::inclusive_scan(std::execution::unseq, std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inc_scan_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it =
            std::inclusive_scan(std::execution::par_unseq, std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_naive_p_sum_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_p_sum_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_inc_scan_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_inc_scan_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_inc_scan_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_inc_scan_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK_MAIN();