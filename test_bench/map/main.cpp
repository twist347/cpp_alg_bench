#include <benchmark/benchmark.h>
#include <execution>

#include "utils.h"
#include "map.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 10'000;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 100'000, finish = 500'000, step = 100'000;

constexpr auto time_unit = benchmark::kMicrosecond;

static auto gb_map_loop_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = map::loop_alg(
            std::cbegin(src), std::cend(src),
            std::begin(dst),
            utils::funcs::newton_sqrt<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_map_openmp_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = map::openmp_alg(
            std::cbegin(src), std::cend(src),
            std::begin(dst),
            utils::funcs::newton_sqrt<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::cbegin(src), std::cend(src),
            std::begin(dst),
            utils::funcs::newton_sqrt<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::execution::par,
            std::cbegin(src), std::cend(src),
            std::begin(dst),
            utils::funcs::newton_sqrt<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::execution::unseq,
            std::cbegin(src), std::cend(src),
            std::begin(dst),
            utils::funcs::newton_sqrt<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src(size), dst(size);
    utils::fill_rnd_range(std::begin(src), std::end(src), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::execution::par_unseq,
            std::cbegin(src), std::cend(src),
            std::begin(dst),
            utils::funcs::newton_sqrt<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_map_loop_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_map_openmp_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_map_transform_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_map_transform_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_map_transform_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_map_transform_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK_MAIN();