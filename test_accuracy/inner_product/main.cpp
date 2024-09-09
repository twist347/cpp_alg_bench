#include <gtest/gtest.h>

#include "inner_product.h"
#include "utils.h"

TEST(InnerProdLoop, NumericTest) {
    constexpr std::size_t size = 10'000;
    std::vector<int> data1(size), data2(size);
    utils::fill_rnd_range(std::begin(data1), std::end(data1), -3, 3);
    utils::fill_rnd_range(std::begin(data2), std::end(data2), -3, 3);

    const auto res1 = inner_prod::loop_alg(std::cbegin(data1), std::cend(data1), std::cbegin(data2), 0);
    const auto res2 = std::inner_product(std::cbegin(data1), std::cend(data1), std::cbegin(data2), 0);
    const auto res3 = std::transform_reduce(std::cbegin(data1), std::cend(data1), std::cbegin(data2), 0);

    ASSERT_EQ(res1, res2);
    ASSERT_EQ(res2, res3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}