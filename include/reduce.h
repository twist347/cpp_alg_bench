#pragma once

#include <algorithm>
#include <iterator>
#include <execution>
#include <future>

namespace reduce {

    template<typename Iter>
    auto acc_loop_alg(Iter first, Iter last) -> typename std::iterator_traits<Iter>::value_type {
        using value_type = typename std::iterator_traits<Iter>::value_type;
        value_type sum = 0;
        for (Iter it = first; it != last; ++it) {
            sum += *it;
        }
        return sum;
    }

    template<typename Iter>
    auto acc_for_each_alg(Iter first, Iter last) -> typename std::iterator_traits<Iter>::value_type {
        using value_type = typename std::iterator_traits<Iter>::value_type;
        value_type sum = 0;
        std::for_each(first, last, [&sum](value_type v) { sum += v; });
        return sum;
    }

    template<std::random_access_iterator Iter>
    auto acc_openmp_alg(Iter first, Iter last) -> typename std::iterator_traits<Iter>::value_type {
        using value_type = typename std::iterator_traits<Iter>::value_type;
        value_type sum = 0;
#pragma omp parallel for reduction(+:sum)
        for (Iter it = first; it != last; ++it) {
            sum += *it;
        }
        return sum;
    }

    namespace detail {

        inline constexpr int MIN_LEN = 100;

    }

    template<typename Iter>
    auto naive_reduce_thread(Iter first, Iter last, typename std::iterator_traits<Iter>::value_type init = 0) {
        using value_type = typename std::iterator_traits<Iter>::value_type;
        const auto length = std::distance(first, last);

        if (length == 0) {
            return init;
        }
        if (length <= detail::MIN_LEN) {
            return std::accumulate(first, first + length, init);
        }

        static auto num_threads = std::thread::hardware_concurrency();
        const auto block_size = length / num_threads;

        std::vector<std::thread> threads(num_threads);
        std::vector<value_type> results(num_threads + 1);

        auto accum_block = [](Iter first_, Iter last_, value_type &res) {
            res = std::accumulate(first_, last_, res);
        };

        std::size_t thread_idx = 0;

        for (;length >= block_size * (thread_idx + 1); first += block_size, ++thread_idx) {
            threads[thread_idx] =
                std::thread(accum_block, first, first + block_size, std::ref(results[thread_idx]));
        }

        const auto remainder = length - block_size * thread_idx;

        if (remainder > 0) {
            accum_block(first, first + remainder, std::ref(results[thread_idx]));
        }

        for (auto &&t : threads) {
            t.join();
        }

        return std::accumulate(results.begin(), results.end(), init);
    }

    template<typename Iter>
    auto naive_reduce_async(Iter first, Iter last, typename std::iterator_traits<Iter>::value_type init = 0) {
        using value_type = typename std::iterator_traits<Iter>::value_type;
        const auto length = std::distance(first, last);

        if (length == 0) {
            return init;
        }
        if (length <= detail::MIN_LEN) {
            return std::accumulate(first, first + length, init);
        }

        static const auto num_threads = std::thread::hardware_concurrency();
        const auto block_size = length / num_threads;

        std::vector<std::future<value_type>> results(num_threads);

        auto accumulate_block = [](Iter first_, Iter last_) {
            return std::accumulate(first_, last_, value_type{});
        };

        std::size_t thread_idx = 0;

        for (;length >= block_size * (thread_idx + 1); first += block_size, ++thread_idx) {
            results[thread_idx] = std::async(accumulate_block, first, first + block_size);
        }

        const auto remainder = length - block_size * thread_idx;
        auto result = init;

        if (remainder > 0) {
            result += accumulate_block(first, first + remainder);
        }

        for (std::size_t i = 0; i < num_threads; ++i) {
            result += results[i].get();
        }

        return result + init;
    }

}
