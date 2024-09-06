#include <gtest/gtest.h>

#include <algorithm>

#include "map.h"
#include "utils.h"

TEST(MapLoopAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    std::vector<int> from(size), to1(size), to2(size);
    utils::fill_rnd_range(std::begin(from), std::end(from), -10, 10);

    constexpr auto closure = [](auto val) { return val * val; };

    const auto res_it1 = map::loop_alg(std::cbegin(from), std::cend(from), std::begin(to1), closure);
    const auto res_it2 = std::transform(std::cbegin(from), std::cend(from), std::begin(to2), closure);

    ASSERT_EQ(res_it1, std::cend(to1));
    ASSERT_EQ(res_it2, std::cend(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(MapOpenMPAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    std::vector<int> from(size), to1(size), to2(size);
    utils::fill_rnd_range(std::begin(from), std::end(from), -10, 10);

    constexpr auto closure = [](auto val) { return val * val; };

    const auto res_it1 = map::openmp_alg(std::cbegin(from), std::cend(from), std::begin(to1), closure);
    const auto res_it2 = std::transform(std::cbegin(from), std::cend(from), std::begin(to2), closure);

    ASSERT_EQ(res_it1, std::cend(to1));
    ASSERT_EQ(res_it2, std::cend(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}