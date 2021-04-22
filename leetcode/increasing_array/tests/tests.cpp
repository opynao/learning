#include "solution.h"
#include "gtest/gtest.h"

TEST(Basic, Test1)
{
    std::vector<int> v{1, 1, 1};
    Solution s;
    EXPECT_EQ(s.minOperations(v), 3);
}

TEST(Basic, Test2)
{
    std::vector<int> v{1, 5, 2, 4, 1};
    Solution s;
    EXPECT_EQ(s.minOperations(v), 14);
}

TEST(Basic, Test3)
{
    std::vector<int> v{1};
    Solution s;
    EXPECT_EQ(s.minOperations(v), 0);
}

TEST(Basic, Test4)
{
    std::vector<int> v{5, 1, 8, 10, 7};
    Solution s;
    EXPECT_EQ(s.minOperations(v), 9);
}

TEST(Basic, Test4)
{
    std::vector<int> v{5, 9, 1, 10, 7};
    Solution s;
    EXPECT_EQ(s.minOperations(v), 15);
}