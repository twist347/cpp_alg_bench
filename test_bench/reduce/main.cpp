#include <benchmark/benchmark.h>
#include <numeric>
#include <execution>

#include "utils.h"
#include "reduce.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 1.0;
constexpr value_type min_val = 0.0;

constexpr std::size_t start = 1'000'000, finish = 10'000'000, step = 1'000'000;

constexpr auto time_unit = benchmark::kMicrosecond;

static auto gb_acc_loop_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = reduce::acc_loop_alg(std::cbegin(data), std::cend(data), static_cast<value_type>(0));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_acc_openmp_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = reduce::acc_openmp_alg(std::cbegin(data), std::cend(data));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_acc_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::accumulate(std::cbegin(data), std::cend(data), static_cast<value_type>(0));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_naive_reduce_thread_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = reduce::naive_reduce_thread(std::cbegin(data), std::cend(data));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_naive_reduce_async_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = reduce::naive_reduce_async(std::cbegin(data), std::cend(data));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_reduce_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::reduce(std::cbegin(data), std::cend(data));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_reduce_par_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::reduce(std::execution::par, std::cbegin(data), std::cend(data));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_reduce_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::reduce(std::execution::unseq, std::cbegin(data), std::cend(data));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_reduce_par_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);
    utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::reduce(std::execution::par_unseq, std::cbegin(data), std::cend(data));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_acc_loop_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_acc_openmp_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_std_acc_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_naive_reduce_thread_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_naive_reduce_async_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_std_reduce_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_reduce_par_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_reduce_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_reduce_par_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK_MAIN();