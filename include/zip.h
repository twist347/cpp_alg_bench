#pragma once

#include <iterator>

namespace zip {

    template<
        std::input_iterator InputIt1, std::input_iterator InputIt2,
        std::output_iterator<typename std::iterator_traits<InputIt1>::value_type> OutputIt,
        typename BinaryOp
    >
    constexpr auto loop_alg(
        InputIt1 first1, InputIt1 last1,
        InputIt2 first2,
        OutputIt d_first,
        BinaryOp op
    ) -> OutputIt {
        for (; first1 != last1; ++d_first, ++first1, ++first2) {
            *d_first = std::invoke(op, *first1, *first2);
        }
        return d_first;
    }

    template<
        std::random_access_iterator RandIt1, std::input_iterator RandIt2,
        std::random_access_iterator DRandIt,
        typename BinaryOp
    >
    auto openmp_alg(
        RandIt1 first1, RandIt1 last1,
        RandIt2 first2,
        DRandIt d_first,
        BinaryOp op
    ) -> DRandIt {
        const auto size = std::distance(first1, last1);
#pragma omp parallel for schedule(guided)
        for (std::size_t i = 0; i < size; ++i) {
            d_first[i] = std::invoke(op, first1[i], first2[i]);
        }
        return d_first + size;
    }

}