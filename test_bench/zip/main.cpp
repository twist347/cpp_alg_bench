#include <benchmark/benchmark.h>
#include <execution>

#include "utils.h"
#include "zip.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 10'000;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 100'000, finish = 500'000, step = 100'000;

constexpr auto time_unit = benchmark::kMillisecond;

static auto gb_zip_loop_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from1(size), from2(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from1), std::end(from1), min_val, max_val);
        utils::fill_rnd_range(std::begin(from2), std::end(from2), min_val, max_val);
        state.ResumeTiming();

        auto res_it = zip::loop_alg(
            std::cbegin(from1), std::cend(from1),
            std::cbegin(from2),
            std::begin(to),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_zip_openmp_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from1(size), from2(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from1), std::end(from1), min_val, max_val);
        utils::fill_rnd_range(std::begin(from2), std::end(from2), min_val, max_val);
        state.ResumeTiming();

        auto res_it = zip::openmp_alg(
            std::cbegin(from1), std::cend(from1),
            std::cbegin(from2),
            std::begin(to),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_zip_transform_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from1(size), from2(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from1), std::end(from1), min_val, max_val);
        utils::fill_rnd_range(std::begin(from2), std::end(from2), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::transform(
            std::cbegin(from1), std::cend(from1),
            std::cbegin(from2),
            std::begin(to),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_zip_transform_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from1(size), from2(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from1), std::end(from1), min_val, max_val);
        utils::fill_rnd_range(std::begin(from2), std::end(from2), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::transform(
            std::execution::par,
            std::cbegin(from1), std::cend(from1),
            std::cbegin(from2),
            std::begin(to),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_zip_transform_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from1(size), from2(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from1), std::end(from1), min_val, max_val);
        utils::fill_rnd_range(std::begin(from2), std::end(from2), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::transform(
            std::execution::unseq,
            std::cbegin(from1), std::cend(from1),
            std::cbegin(from2),
            std::begin(to),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_zip_transform_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type to(size), from1(size), from2(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(from1), std::end(from1), min_val, max_val);
        utils::fill_rnd_range(std::begin(from2), std::end(from2), min_val, max_val);
        state.ResumeTiming();

        auto res_it = std::transform(
            std::execution::par_unseq,
            std::cbegin(from1), std::cend(from1),
            std::cbegin(from2),
            std::begin(to),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

constexpr std::size_t iter_num = 2;

BENCHMARK(gb_zip_loop_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_zip_openmp_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_zip_transform_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_zip_transform_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_zip_transform_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_zip_transform_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);

BENCHMARK_MAIN();