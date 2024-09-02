#pragma once

#include <execution>
#include <iterator>

namespace map {

    template<typename InIter, typename OutIter, typename Func>
    auto map_loop_alg(InIter in_first, InIter in_last, OutIter out_first, Func func) -> void {
        for (auto in_it = in_first; in_it != in_last; ++in_it) {
            *out_first++ = func(*in_it);
        }
    }

    template<std::random_access_iterator InIter, std::random_access_iterator OutIter, typename Func>
    auto map_openmp_alg(InIter in_first, InIter in_last, OutIter out_first, Func func) -> void {
        const auto n = std::distance(in_first, in_last);
#pragma omp parallel for schedule(guided)
        for (std::size_t i = 0; i < n; ++i) {
            *(out_first + i) = func(*(in_first + i));
        }
    }

}
