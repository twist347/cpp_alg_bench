#pragma once

#include <iterator>
#include <cstring>

namespace copy {

    template<
        std::input_iterator InputIt,
        std::output_iterator<typename std::iterator_traits<InputIt>::value_type> OutputIt
    >
    constexpr auto naive_loop_alg(InputIt first, InputIt last, OutputIt d_first) -> OutputIt {
        for (; first != last; ++first, ++d_first) {
            *d_first = *first;
        }
        return d_first;
    }

    // If d_first is in [first, last), the behavior is undefined
    // https://en.cppreference.com/w/cpp/algorithm/copy
    template<
        std::input_iterator InputIt,
        std::output_iterator<typename std::iterator_traits<InputIt>::value_type> OutputIt
    >
    constexpr auto loop_alg(InputIt first, InputIt last, OutputIt d_first) -> OutputIt {
        using value_type = typename std::iterator_traits<InputIt>::value_type;

        if constexpr (
            std::is_trivially_copyable_v<value_type> &&
            std::contiguous_iterator<InputIt> &&
            std::contiguous_iterator<OutputIt>
        ) {
            const auto size = std::distance(first, last);
            std::memcpy(&(*d_first), &(*first), size * sizeof(value_type));
            return d_first + size;
        } else {
            return naive_loop_alg(first, last, d_first);
        }
    }

    template<
        std::random_access_iterator RandomIt,
        std::random_access_iterator DRandomIt
    >
    auto openmp_alg(RandomIt first, RandomIt last, DRandomIt d_first) -> DRandomIt {
        const auto n = std::distance(first, last);
#pragma omp parallel for simd schedule(guided)
        for (std::size_t i = 0; i < n; ++i) {
            d_first[i] = first[i];
        }
        return d_first + n;
    }

}