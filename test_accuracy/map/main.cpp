#include <gtest/gtest.h>

#include <algorithm>

#include "map.h"
#include "utils.h"

TEST(MapLoopAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    std::vector<int> from(size), to1(size), to2(size);
    utils::fill_data(std::begin(from), std::end(from), -10, 10);

    map::map_loop_alg(std::cbegin(from), std::cend(from), std::begin(to1), [](auto val) { return val * val; });
    std::transform(std::cbegin(from), std::cend(from), std::begin(to2), [](auto val) { return val * val; });

    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(MapOpenMPAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    std::vector<int> from(size), to1(size), to2(size);
    utils::fill_data(std::begin(from), std::end(from), -10, 10);

    map::map_openmp_alg(std::cbegin(from), std::cend(from), std::begin(to1), [](auto val) { return val * val; });
    std::transform(std::cbegin(from), std::cend(from), std::begin(to2), [](auto val) { return val * val; });

    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}