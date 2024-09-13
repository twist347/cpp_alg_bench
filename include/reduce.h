#pragma once

#include <algorithm>
#include <iterator>
#include <execution>
#include <future>

namespace reduce {

    template<std::input_iterator InputIt, typename Value, typename BinaryOp>
    constexpr auto acc_loop_alg(InputIt first, InputIt last, Value init, BinaryOp op) -> Value {
        for (; first != last; ++first) {
            init = std::invoke(op, std::move(init), *first);
        }
        return init;
    }

    template<std::input_iterator InputIt, typename Value>
    constexpr auto acc_loop_alg(InputIt first, InputIt last, Value init) -> Value {
        return acc_loop_alg(first, last, init, std::plus());
    }

    template<std::random_access_iterator RandIt, typename Value>
    auto acc_openmp_alg(RandIt first, RandIt last, Value init) -> Value {
        const auto size = std::distance(first, last);
#pragma omp parallel for simd reduction(+:init) schedule(guided)
        for (std::ptrdiff_t i = 0; i < size; ++i) {
            init += first[i];
        }
        return init;
    }

    template<std::input_iterator InputIt>
    auto acc_openmp_alg(
        InputIt first, InputIt last
    ) -> typename std::iterator_traits<InputIt>::value_type {
        return acc_openmp_alg(first, last, typename std::iterator_traits<InputIt>::value_type{});
    }

    template<std::forward_iterator ForwardIt, typename Value>
    auto naive_reduce_thread(ForwardIt first, ForwardIt last, Value init) -> Value {
        static constexpr std::size_t MIN_LEN = 100;
        const auto length = std::distance(first, last);

        if (length == 0) {
            return init;
        }
        if (length <= MIN_LEN) {
            return std::accumulate(first, last, init);
        }

        static const auto num_threads = std::thread::hardware_concurrency();
        const auto block_size = length / num_threads;

        std::vector<Value> results(num_threads);
        std::vector<std::thread> threads;
        threads.reserve(num_threads);

        constexpr auto accumulate_block = [](ForwardIt first_, ForwardIt last_, Value &res) {
            res = std::accumulate(first_, last_, res);
        };

        auto it = first;
        for (std::size_t i = 0; i < num_threads - 1; ++i, std::advance(it, block_size)) {
            threads.emplace_back(accumulate_block, it, std::next(it, block_size), std::ref(results[i]));
        }

        threads.emplace_back(accumulate_block, it, last, std::ref(results[num_threads - 1]));

        for (auto &t: threads) {
            t.join();
        }

        return std::accumulate(results.cbegin(), results.cend(), init);
    }

    template<std::forward_iterator ForwardIt>
    auto naive_reduce_thread(
        ForwardIt first, ForwardIt last
    ) -> typename std::iterator_traits<ForwardIt>::value_type {
        return naive_reduce_thread(first, last, typename std::iterator_traits<ForwardIt>::value_type{});
    }

    template<std::forward_iterator ForwardIt, typename Value>
    auto naive_reduce_async(ForwardIt first, ForwardIt last, Value init) -> Value {
        static constexpr std::size_t MIN_LEN = 100;
        const auto length = std::distance(first, last);

        if (length == 0) {
            return init;
        }
        if (length <= MIN_LEN) {
            return std::accumulate(first, last, init);
        }

        static const auto num_threads = std::thread::hardware_concurrency();
        const auto block_size = length / num_threads;

        std::vector<std::future<Value>> results;
        results.reserve(num_threads);

        auto block_start = first;
        for (std::size_t i = 0; i < num_threads - 1; ++i) {
            const auto block_end = block_start + block_size;

            results.emplace_back(std::async(std::launch::async, [block_start, block_end, init] {
                return std::accumulate(block_start, block_end, init);
            }));

            block_start = block_end;
        }

        auto result = std::accumulate(block_start, last, init);

        for (auto &future: results) {
            result += future.get();
        }

        return result;
    }

    template<std::forward_iterator ForwardIt>
    auto naive_reduce_async(
        ForwardIt first, ForwardIt last
    ) -> typename std::iterator_traits<ForwardIt>::value_type {
        return naive_reduce_async(first, last, typename std::iterator_traits<ForwardIt>::value_type{});
    }

}
