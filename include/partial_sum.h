#pragma once

#include <iterator>

namespace par_sum {

    template<
        std::input_iterator InputIt,
        std::output_iterator<typename std::iterator_traits<InputIt>::value_type> OutputIt,
        typename BinaryOp
    >
    constexpr auto naive_partial_sum(InputIt first, InputIt last, OutputIt d_first, BinaryOp op) -> OutputIt {
        using value_type = typename std::iterator_traits<InputIt>::value_type;

        if (first == last) {
            return d_first;
        }

        value_type acc = *first;
        *d_first = acc;

        while (++first != last) {
            acc = std::invoke(op, std::move(acc), *first);
            *++d_first = acc;
        }

        return ++d_first;
    }

    template<
        std::input_iterator InputIt,
        std::output_iterator<typename std::iterator_traits<InputIt>::value_type> OutputIt
    >
    constexpr auto naive_partial_sum(InputIt first, InputIt last, OutputIt d_first) -> OutputIt {
        return naive_partial_sum(first, last, d_first, std::plus());
    }

}