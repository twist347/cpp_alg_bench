#include <benchmark/benchmark.h>

#include "utils.h"

/*
 *  NOTE:
 *  comparison of sorting function speed depending on comparator type (func, method, lambda)
 *  GCC vs Clang
 */

using value_type = int;
using container_type = std::vector<value_type>;

constexpr value_type max_val = 10'000;
constexpr value_type min_val = -max_val;

constexpr std::size_t start = 1'000'000, finish = 5'000'000, step = 1'000'000;

constexpr auto time_unit = benchmark::kMillisecond;

template<typename Value>
auto cmp_func(Value lhs, Value rhs) -> bool {
    return lhs < rhs;
}

template<typename Value>
struct Comparator {

    auto operator()(Value lhs, Value rhs) const {
        return lhs < rhs;
    }

};

constexpr auto cmp_closure = []<typename Value>(Value lhs, Value rhs) { return lhs < rhs; };

static auto gb_std_sort_func_cmp_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::begin(data), std::end(data), cmp_func<value_type>);

        benchmark::ClobberMemory();
    }
}

static auto gb_std_sort_struct_cmp_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::begin(data), std::end(data), Comparator<value_type>{});

        benchmark::ClobberMemory();
    }
}

static auto gb_std_sort_closure_cmp_bench(benchmark::State &state) -> void {
    const auto size = state.range(0);
    container_type data(size);

    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        utils::fill_rnd_range(std::begin(data), std::end(data), min_val, max_val);
        state.ResumeTiming();

        std::sort(std::begin(data), std::end(data), cmp_closure);

        benchmark::ClobberMemory();
    }
}

constexpr double min_wu_t = 1.0;

BENCHMARK(gb_std_sort_func_cmp_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_sort_struct_cmp_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);
BENCHMARK(gb_std_sort_closure_cmp_bench)->DenseRange(start, finish, step)->Unit(time_unit)->MinWarmUpTime(min_wu_t);

BENCHMARK_MAIN();