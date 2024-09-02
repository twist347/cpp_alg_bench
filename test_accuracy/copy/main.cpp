#include <gtest/gtest.h>

#include "copy.h"
#include "utils.h"

TEST(CopyLoopAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    const double max_v = 100'000, min_v = -max_v;
    std::vector<double> from(size), to1(size), to2(size);
    utils::fill_data(std::begin(from), std::end(from), min_v, max_v);

    copy::copy_loop_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(CopyLoopAlg, StringTest) {
    constexpr std::size_t size = 100'000;
    std::string from(size, char{}), to1(size, char{}), to2(size, char{});
    utils::fill_rnd_str(std::begin(from), std::end(from));

    copy::copy_loop_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(to1, to2);
}

TEST(CopyOpenMPAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    const double max_v = 100'000, min_v = -max_v;
    std::vector<double> from(size), to1(size), to2(size);
    utils::fill_data(std::begin(from), std::end(from), min_v, max_v);

    copy::copy_openmp_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(CopyOpenMPAlg, StringTest) {
    constexpr std::size_t size = 100'000;
    std::string from(size, char{}), to1(size, char{}), to2(size, char{});
    utils::fill_rnd_str(std::begin(from), std::end(from));

    copy::copy_openmp_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(to1, to2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}