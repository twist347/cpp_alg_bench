#include <execution>
#include <benchmark/benchmark.h>

#include "utils.h"

using value_type = double;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 10'000;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 100'000, finish = 500'000, step = 100'000;

constexpr auto time_unit = benchmark::kMillisecond;

template<typename Value>
constexpr auto qsort_cmp_asc(const void *lhs, const void *rhs) -> Value {
    return *static_cast<const Value *>(lhs) - *static_cast<const Value *>(rhs);
}

static auto gb_qsort_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::qsort(std::data(data), data.size(), sizeof(value_type), qsort_cmp_asc);

        benchmark::ClobberMemory();
    }
}

static auto gb_sort_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_sort_par_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::execution::par, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_sort_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::execution::unseq, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

static auto gb_sort_par_unseq_alg_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_data(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::execution::par_unseq, std::begin(data), std::end(data));

        benchmark::ClobberMemory();
    }
}

constexpr std::size_t iter_num = 50;

BENCHMARK(gb_qsort_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_sort_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_sort_par_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_sort_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);
BENCHMARK(gb_sort_par_unseq_alg_bench)->DenseRange(start, finish, step)->Unit(time_unit)->Iterations(iter_num);

BENCHMARK_MAIN();