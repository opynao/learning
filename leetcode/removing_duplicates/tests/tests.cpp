#include "gtest/gtest.h"
#include "solution.h"

TEST(Basic, Test1)
{
    std::vector<int> v {1,1,2};
    Solution s;
    EXPECT_EQ(s.removeDublicates(v), 2);
}