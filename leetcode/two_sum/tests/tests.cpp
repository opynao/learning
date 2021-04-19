#include "two_sum.h"
#include "gtest/gtest.h"

TEST(Basic, Test1)
{
    std::vector<int> v{2, 7, 11, 15};
    int target{9};
    TwoSum ts;
    auto result = ts.FindPos(v, target);
    std::vector<int> expected{0, 1};
    EXPECT_EQ(result, expected);
}