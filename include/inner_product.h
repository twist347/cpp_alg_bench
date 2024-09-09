#pragma once

#include <iterator>
#include <functional>

namespace inner_prod {

    template<
        std::input_iterator InputIt1, std::input_iterator InputIt2,
        typename Value,
        typename BinaryOp1, typename BinaryOp2>
    constexpr auto loop_alg(
        InputIt1 first1, InputIt1 last1,
        InputIt2 first2,
        Value init,
        BinaryOp1 op1, BinaryOp2 op2
    ) -> Value {
        while (first1 != last1) {
            init = std::invoke(op1, std::move(init), std::invoke(op2, *first1, *first2));
            ++first1;
            ++first2;
        }
        return init;
    }

    template<std::input_iterator InputIt1, std::input_iterator InputIt2, typename Value>
    constexpr auto loop_alg(InputIt1 first1, InputIt1 last1, InputIt2 first2, Value init) -> Value {
        return inner_product(first1, last1, first2, init, std::plus(), std::multiplies());
    }

    template<std::random_access_iterator RandIt1, std::input_iterator RandIt2, typename Value>
    auto openmp_alg(
        RandIt1 first1, RandIt1 last1,
        RandIt2 first2,
        Value init
    ) -> Value {
        const auto size = std::distance(first1, last1);

#pragma omp parallel for reduction(+:init) schedule(guided)
        for (std::ptrdiff_t i = 0; i < size; ++i) {
            init += (*(first1 + i)) * (*(first2 + i));
        }
        return init;
    }

}