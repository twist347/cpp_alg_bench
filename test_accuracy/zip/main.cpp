#include <gtest/gtest.h>

#include <algorithm>

#include "zip.h"
#include "utils.h"

TEST(ZipLoopAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    std::vector<int> from1(size), from2(size), to1(size), to2(size);
    utils::fill_rnd_range(std::begin(from1), std::end(from1), -10, 10);
    utils::fill_rnd_range(std::begin(from2), std::end(from2), -10, 10);

    constexpr auto closure = [](auto lhs, auto rhs) { return lhs * lhs + rhs * rhs; };

    const auto res_it1 = zip::loop_alg(
        std::cbegin(from1), std::cend(from1),
        std::cbegin(from2),
        std::begin(to1),
        closure
    );

    const auto res_it2 = std::transform(
        std::cbegin(from1), std::cend(from1),
        std::cbegin(from2),
        std::begin(to2),
        closure
    );

    ASSERT_EQ(res_it1, std::cend(to1));
    ASSERT_EQ(res_it2, std::cend(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(ZipOpenMPAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    std::vector<int> from1(size), from2(size), to1(size), to2(size);
    utils::fill_rnd_range(std::begin(from1), std::end(from1), -10, 10);
    utils::fill_rnd_range(std::begin(from2), std::end(from2), -10, 10);

    constexpr auto closure = [](auto lhs, auto rhs) { return lhs * lhs + rhs * rhs; };

    const auto res_it1 = zip::openmp_alg(
        std::cbegin(from1), std::cend(from1),
        std::cbegin(from2),
        std::begin(to1),
        closure
    );

    const auto res_it2 = std::transform(
        std::cbegin(from1), std::cend(from1),
        std::cbegin(from2),
        std::begin(to2),
        closure
    );

    ASSERT_EQ(res_it1, std::cend(to1));
    ASSERT_EQ(res_it2, std::cend(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}