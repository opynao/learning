#include "sign.h"
#include "gtest/gtest.h"

TEST(Basic, Test1)
{
    std::vector<int> v{-1, -2, -3, -4, 3, 2, 1};
    ProductSign ps;
    EXPECT_EQ(ps.arraySign(v), 1);
}

TEST(Basic, Test2)
{
    std::vector<int> v{1, 5, 0, 2, -3};
    ProductSign ps;
    EXPECT_EQ(ps.arraySign(v), 0);
}

TEST(Basic, Test3)
{
    std::vector<int> v{-1, 1, -1, 1, -1};
    ProductSign ps;
    EXPECT_EQ(ps.arraySign(v), -1);
}