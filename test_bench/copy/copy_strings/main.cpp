#include <benchmark/benchmark.h>
#include <execution>

#include "utils.h"
#include "copy.h"

using value_type = std::string;
using container_type = std::vector<value_type>;

constexpr std::size_t str_size = 100;

constexpr std::size_t start = 500'000, finish = 1'000'000, step = 250'000;

constexpr auto time_unit = benchmark::kMicrosecond;

static auto gb_naive_loop_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size, value_type(str_size, char{})), dst(size, value_type(str_size, char{}));
    for (auto &s : src) {
        utils::fill_rnd_str(s.begin(), s.end());
    }

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = copy::naive_loop_alg(std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_loop_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size, value_type(str_size, char{})), dst(size, value_type(str_size, char{}));
    for (auto &s : src) {
        utils::fill_rnd_str(s.begin(), s.end());
    }

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = copy::loop_alg(std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_openmp_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size, value_type(str_size, char{})), dst(size, value_type(str_size, char{}));
    for (auto &s : src) {
        utils::fill_rnd_str(s.begin(), s.end());
    }

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = copy::openmp_alg(std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size, value_type(str_size, char{})), dst(size, value_type(str_size, char{}));
    for (auto &s : src) {
        utils::fill_rnd_str(s.begin(), s.end());
    }

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::copy(std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size, value_type(str_size, char{})), dst(size, value_type(str_size, char{}));
    for (auto &s : src) {
        utils::fill_rnd_str(s.begin(), s.end());
    }

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::copy(std::execution::par, std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size, value_type(str_size, char{})), dst(size, value_type(str_size, char{}));
    for (auto &s : src) {
        utils::fill_rnd_str(s.begin(), s.end());
    }

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::copy(std::execution::unseq, std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_copy_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size, value_type(str_size, char{})), dst(size, value_type(str_size, char{}));
    for (auto &s : src) {
        utils::fill_rnd_str(s.begin(), s.end());
    }

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::copy(std::execution::par_unseq, std::cbegin(src), std::cend(src), std::begin(dst));

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_naive_loop_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_loop_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_openmp_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_copy_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_copy_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_copy_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_copy_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK_MAIN();