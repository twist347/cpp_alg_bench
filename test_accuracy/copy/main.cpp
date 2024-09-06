#include <gtest/gtest.h>

#include "copy.h"
#include "utils.h"

TEST(CopyNaiveLoopAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    const double max_v = 100'000, min_v = -max_v;
    std::vector<double> from(size), to1(size), to2(size);
    utils::fill_rnd_range(std::begin(from), std::end(from), min_v, max_v);

    const auto res_it1 = copy::naive_loop_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    const auto res_it2 = std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(res_it1, std::end(to1));
    ASSERT_EQ(res_it2, std::end(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(CopyNaiveLoopAlg, StringTest) {
    constexpr std::size_t data_size = 100'000, str_size = 100;
    std::vector<std::string> from(data_size, std::string(str_size, char{})), to1(data_size), to2(data_size);
    for (auto &s : from) {
         utils::fill_rnd_str(std::begin(s), std::end(s));
    }

    const auto res_it1 = copy::naive_loop_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    const auto res_it2 = std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(res_it1, std::end(to1));
    ASSERT_EQ(res_it2, std::end(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(CopyLoopAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    const double max_v = 100'000, min_v = -max_v;
    std::vector<double> from(size), to1(size), to2(size);
    utils::fill_rnd_range(std::begin(from), std::end(from), min_v, max_v);

    const auto res_it1 = copy::loop_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    const auto res_it2 = std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(res_it1, std::end(to1));
    ASSERT_EQ(res_it2, std::end(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(CopyLoopAlg, StringTest) {
    constexpr std::size_t data_size = 100'000, str_size = 100;
    std::vector<std::string> from(data_size, std::string(str_size, char{})), to1(data_size), to2(data_size);
    for (auto &s : from) {
        utils::fill_rnd_str(std::begin(s), std::end(s));
    }

    const auto res_it1 = copy::loop_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    const auto res_it2 = std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(res_it1, std::end(to1));
    ASSERT_EQ(res_it2, std::end(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(CopyOpenMPAlg, NumericTest) {
    constexpr std::size_t size = 100'000;
    const double max_v = 100'000, min_v = -max_v;
    std::vector<double> from(size), to1(size), to2(size);
    utils::fill_rnd_range(std::begin(from), std::end(from), min_v, max_v);

    const auto res_it1 = copy::openmp_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    const auto res_it2 = std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(res_it1, std::end(to1));
    ASSERT_EQ(res_it2, std::end(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

TEST(CopyOpenMPAlg, StringTest) {
    constexpr std::size_t data_size = 100'000, str_size = 100;
    std::vector<std::string> from(data_size, std::string(str_size, char{})), to1(data_size), to2(data_size);
    for (auto &s : from) {
        utils::fill_rnd_str(std::begin(s), std::end(s));
    }

    const auto res_it1 = copy::openmp_alg(std::cbegin(from), std::cend(from), std::begin(to1));
    const auto res_it2 = std::copy(std::cbegin(from), std::cend(from), std::begin(to2));

    ASSERT_EQ(res_it1, std::end(to1));
    ASSERT_EQ(res_it2, std::end(to2));
    ASSERT_TRUE(std::equal(std::cbegin(to1), std::cend(to1), std::cbegin(to2)));
}

int main(int argc, char **argv) {
    std::cout << "copy accuracy tests with ASan, LSan, UBSan" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}