#pragma once

#include <iterator>
#include <functional>

namespace map {

    template<
        std::input_iterator InputIt,
        std::output_iterator<typename std::iterator_traits<InputIt>::value_type> OutputIt,
        typename UnaryOp
    >
    constexpr auto loop_alg(InputIt first, InputIt last, OutputIt d_first, UnaryOp op) -> OutputIt {
        for (; first != last; ++first, ++d_first) {
            *d_first = std::invoke(op, *first);
        }
        return d_first;
    }

    // random access iterator because of perf
    template<
        std::random_access_iterator RandomIt,
        std::random_access_iterator DRandomIt,
        typename UnaryOp
    >
    auto openmp_alg(RandomIt first, RandomIt last, DRandomIt d_first, UnaryOp op) -> DRandomIt {
        const auto n = std::distance(first, last);
#pragma omp parallel for simd schedule(guided)
        for (std::size_t i = 0; i < n; ++i) {
            d_first[i] = std::invoke(op, first[i]);
        }
        return d_first + n;
    }

}
