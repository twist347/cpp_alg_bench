#include <benchmark/benchmark.h>
#include <execution>

#include "utils.h"
#include "zip.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 10'000;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 10'000, finish = 100'000, step = 10'000;

constexpr auto time_unit = benchmark::kMicrosecond;

static auto gb_zip_loop_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src1(size), src2(size), dst(size);
    utils::fill_rnd_range(std::begin(src1), std::end(src1), min_val, max_val);
    utils::fill_rnd_range(std::begin(src2), std::end(src2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = zip::loop_alg(
            std::cbegin(src1), std::cend(src1),
            std::cbegin(src2),
            std::begin(dst),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_zip_openmp_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src1(size), src2(size), dst(size);
    utils::fill_rnd_range(std::begin(src1), std::end(src1), min_val, max_val);
    utils::fill_rnd_range(std::begin(src2), std::end(src2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = zip::openmp_alg(
            std::cbegin(src1), std::cend(src1),
            std::cbegin(src2),
            std::begin(dst),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_transform_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src1(size), src2(size), dst(size);
    utils::fill_rnd_range(std::begin(src1), std::end(src1), min_val, max_val);
    utils::fill_rnd_range(std::begin(src2), std::end(src2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::cbegin(src1), std::cend(src1),
            std::cbegin(src2),
            std::begin(dst),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_transform_par_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src1(size), src2(size), dst(size);
    utils::fill_rnd_range(std::begin(src1), std::end(src1), min_val, max_val);
    utils::fill_rnd_range(std::begin(src2), std::end(src2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::execution::par,
            std::cbegin(src1), std::cend(src1),
            std::cbegin(src2),
            std::begin(dst),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_transform_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src1(size), src2(size), dst(size);
    utils::fill_rnd_range(std::begin(src1), std::end(src1), min_val, max_val);
    utils::fill_rnd_range(std::begin(src2), std::end(src2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::execution::unseq,
            std::cbegin(src1), std::cend(src1),
            std::cbegin(src2),
            std::begin(dst),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_transform_par_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src1(size), src2(size), dst(size);
    utils::fill_rnd_range(std::begin(src1), std::end(src1), min_val, max_val);
    utils::fill_rnd_range(std::begin(src2), std::end(src2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res_it = std::transform(
            std::execution::par_unseq,
            std::cbegin(src1), std::cend(src1),
            std::cbegin(src2),
            std::begin(dst),
            utils::funcs::gauss_elimination<value_type>
        );

        benchmark::DoNotOptimize(res_it);
        benchmark::ClobberMemory();
    }
}

static auto gb_std_ranges_transform_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type src1(size), src2(size), dst(size);
    utils::fill_rnd_range(std::begin(src1), std::end(src1), min_val, max_val);
    utils::fill_rnd_range(std::begin(src2), std::end(src2), min_val, max_val);

    for ([[maybe_unused]] auto _ : state) {
        auto res = std::ranges::transform(src1, src2, std::begin(dst), utils::funcs::gauss_elimination<value_type>);

        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_zip_loop_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_zip_openmp_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_std_transform_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_transform_par_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_transform_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_transform_par_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_std_ranges_transform_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK_MAIN();