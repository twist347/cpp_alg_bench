#include <benchmark/benchmark.h>

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
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        map::map_loop_alg(
            std::cbegin(from), std::cend(from),
            std::begin(to),
            utils::hard_func<value_type>
        );

        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        std::transform(
            std::cbegin(from), std::cend(from),
            std::begin(to),
            utils::hard_func<value_type>
        );

        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        std::transform(
            std::execution::par,
            std::cbegin(from), std::cend(from),
            std::begin(to),
            utils::hard_func<value_type>
        );

        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        std::transform(
            std::execution::unseq,
            std::cbegin(from), std::cend(from),
            std::begin(to),
            utils::hard_func<value_type>
        );

        benchmark::ClobberMemory();
    }
}

static auto gb_map_transform_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        std::transform(
            std::execution::par_unseq,
            std::cbegin(from), std::cend(from),
            std::begin(to),
            utils::hard_func<value_type>
        );

        benchmark::ClobberMemory();
    }
}

static auto gb_map_openmp_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(from), std::end(from), min_val, max_val);
        state.ResumeTiming();

        map::map_openmp_alg(
            std::cbegin(from), std::cend(from),
            std::begin(to),
            utils::hard_func<value_type>
        );

        benchmark::ClobberMemory();
    }
}

constexpr std::size_t iter_num = 100;

BENCHMARK(gb_map_loop_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_map_transform_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_map_transform_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_map_transform_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_map_transform_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_map_openmp_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);

BENCHMARK_MAIN();