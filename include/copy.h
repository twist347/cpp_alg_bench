#pragma once

#include <iterator>

namespace copy {

    template<typename InIter, typename OutIter>
    auto copy_loop_alg(InIter in_first, InIter in_last, OutIter out_first) -> void {
        for (auto it = in_first; it != in_last; ++it) {
            *out_first++ = *it;
        }
    }

    template<std::random_access_iterator InIter, typename OutIter>
    auto copy_openmp_alg(InIter in_first, InIter in_last, OutIter out_first) -> void {
        const auto n = std::distance(in_first, in_last);

#pragma omp parallel for schedule(guided)
        for (std::size_t i = 0; i < n; ++i) {
            *(out_first + i) = *(in_first + i);
        }
    }

}