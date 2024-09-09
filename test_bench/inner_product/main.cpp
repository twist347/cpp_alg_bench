#include <benchmark/benchmark.h>
#include <numeric>
#include <execution>

#include "utils.h"
#include "inner_product.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 1.0;
constexpr value_type min_val = 0.0;

constexpr std::size_t start = 2'500'000, finish = 10'000'000, step = 2'500'000;

constexpr auto time_unit = benchmark::kMicrosecond;

static auto gb_inner_prod_loop_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data1(size), data2(size);
    utils::fill_rnd_range(std::begin(data1), std::end(data1), min_val, max_val);
    utils::fill_rnd_range(std::begin(data2), std::end(data2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res =
            inner_prod::loop_alg(std::cbegin(data1), std::cend(data1), std::cbegin(data2), static_cast<value_type>(0));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_inner_prod_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data1(size), data2(size);
    utils::fill_rnd_range(std::begin(data1), std::end(data1), min_val, max_val);
    utils::fill_rnd_range(std::begin(data2), std::end(data2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res =
            std::inner_product(std::cbegin(data1), std::cend(data1), std::cbegin(data2), static_cast<value_type>(0));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_tr_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data1(size), data2(size);
    utils::fill_rnd_range(std::begin(data1), std::end(data1), min_val, max_val);
    utils::fill_rnd_range(std::begin(data2), std::end(data2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res =
             std::transform_reduce(std::cbegin(data1), std::cend(data1), std::cbegin(data2), static_cast<value_type>(0));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_tr_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data1(size), data2(size);
    utils::fill_rnd_range(std::begin(data1), std::end(data1), min_val, max_val);
    utils::fill_rnd_range(std::begin(data2), std::end(data2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::transform_reduce(
            std::execution::par,
            std::cbegin(data1), std::cend(data1),
            std::cbegin(data2),
            static_cast<value_type>(0)
        );

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_tr_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data1(size), data2(size);
    utils::fill_rnd_range(std::begin(data1), std::end(data1), min_val, max_val);
    utils::fill_rnd_range(std::begin(data2), std::end(data2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::transform_reduce(
                std::execution::unseq,
                std::cbegin(data1), std::cend(data1),
                std::cbegin(data2),
                static_cast<value_type>(0)
        );

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_tr_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data1(size), data2(size);
    utils::fill_rnd_range(std::begin(data1), std::end(data1), min_val, max_val);
    utils::fill_rnd_range(std::begin(data2), std::end(data2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::transform_reduce(
                std::execution::par_unseq,
                std::cbegin(data1), std::cend(data1),
                std::cbegin(data2),
                static_cast<value_type>(0)
        );

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_inner_prod_loop_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_inner_prod_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_tr_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_tr_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_tr_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_tr_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);;

BENCHMARK_MAIN();