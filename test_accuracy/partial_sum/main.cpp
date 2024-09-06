#include <gtest/gtest.h>

#include <algorithm>

#include "partial_sum.h"
#include "utils.h"

TEST(ParSumNaiveAlg, NumericSumTest) {
    constexpr std::size_t size = 1'000;
    std::vector<double> from(size), to1(size), to2(size), to3(size);
    utils::fill_rnd_range(std::begin(from), std::end(from), -3, 3);

    const auto res_it1 = par_sum::naive_partial_sum(std::cbegin(from), std::cend(from), std::begin(to1));
    const auto res_it2 = std::partial_sum(std::cbegin(from), std::cend(from), std::begin(to2));
    const auto res_it3 = std::inclusive_scan(std::cbegin(from), std::cend(from), std::begin(to3));

    ASSERT_EQ(res_it1, std::cend(to1));
    ASSERT_EQ(res_it2, std::cend(to2));
    ASSERT_EQ(res_it3, std::cend(to3));

    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
    ASSERT_TRUE(std::equal(std::cbegin(to2), std::cend(to2), std::cbegin(to3)));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
