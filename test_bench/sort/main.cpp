#include <benchmark/benchmark.h>
#include <execution>

#include "utils.h"

using value_type = int;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 10'000;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 250'000, finish = 2'000'000, step = 250'000;

constexpr auto time_unit = benchmark::kMicrosecond;

template<typename Value>
constexpr auto qsort_cmp_asc(const void *lhs, const void *rhs) -> Value {
    return *static_cast<const Value *>(lhs) - *static_cast<const Value *>(rhs);
}

static auto gb_qsort_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::qsort(std::data(data), std::size(data), sizeof(value_type), qsort_cmp_asc);

        benchmark::ClobberMemory();
    }
}

static auto gb_std_sort_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_sort_par_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::execution::par, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_sort_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::execution::unseq, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_sort_par_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::execution::par_unseq, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_stable_sort_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::stable_sort(std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_stable_sort_par_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::stable_sort(std::execution::par, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_stable_sort_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::stable_sort(std::execution::unseq, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_stable_sort_par_unseq_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::stable_sort(std::execution::par_unseq, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_std_ranges_sort_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::ranges::sort(data);

        benchmark::ClobberMemory();
    }
}

static auto gb_std_ranges_stable_sort_alg(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::ranges::stable_sort(data);

        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_qsort_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_std_sort_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_sort_par_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_sort_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_sort_par_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_std_stable_sort_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_stable_sort_par_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_stable_sort_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_stable_sort_par_unseq_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK(gb_std_ranges_sort_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_ranges_stable_sort_alg)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK_MAIN();