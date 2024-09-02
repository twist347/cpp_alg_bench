#include <gtest/gtest.h>

#include "reduce.h"
#include "utils.h"

TEST(ReduceLoop, NumericTest) {
    constexpr std::size_t size = 10'000;
    std::vector<int> data(size);
    utils::fill_data(std::begin(data), std::end(data), -3, 3);

    const auto res1 = std::accumulate(std::cbegin(data), std::cend(data), 0);
    const auto res2 = reduce::acc_loop_alg(std::cbegin(data), std::cend(data));

    ASSERT_EQ(res1, res2);
}

TEST(ReduceForEach, NumericTest) {
    constexpr std::size_t size = 10'000;
    std::vector<int> data(size);
    utils::fill_data(std::begin(data), std::end(data), -3, 3);

    const auto res1 = std::accumulate(std::cbegin(data), std::cend(data), 0);
    const auto res2 = reduce::acc_for_each_alg(std::cbegin(data), std::cend(data));

    ASSERT_EQ(res1, res2);
}

TEST(ReduceOpenMP, NumericTest) {
    constexpr std::size_t size = 10'000;
    std::vector<int> data(size);
    utils::fill_data(std::begin(data), std::end(data), -3, 3);

    const auto res1 = std::accumulate(std::cbegin(data), std::cend(data), 0);
    const auto res2 = reduce::acc_openmp_alg(std::cbegin(data), std::cend(data));

    ASSERT_EQ(res1, res2);
}

TEST(ReduceNaiveThread, NumericTest) {
    constexpr std::size_t size = 10'000;
    std::vector<int> data(size);
    utils::fill_data(std::begin(data), std::end(data), -3, 3);

    const auto res1 = std::accumulate(std::cbegin(data), std::cend(data), 0);
    const auto res2 = reduce::naive_reduce_thread(std::cbegin(data), std::cend(data));

    ASSERT_EQ(res1, res2);
}

TEST(ReduceNaiveAsync, NumericTest) {
    constexpr std::size_t size = 10'000;
    std::vector<int> data(size);
    utils::fill_data(std::begin(data), std::end(data), -3, 3);

    const auto res1 = std::accumulate(std::cbegin(data), std::cend(data), 0);
    const auto res2 = reduce::naive_reduce_async(std::cbegin(data), std::cend(data));

    ASSERT_EQ(res1, res2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}