#include "gtest/gtest.h"
#include "pangram.h"

TEST(Basic, Test1)
{
    Pangram pg;
    EXPECT_EQ(pg.CheckIfPangram("thequickbrownfoxjumpsoverthelazydog"), true);
}

TEST(Basic, Test2)
{
    Pangram pg;
    EXPECT_EQ(pg.CheckIfPangram("leetcode"), false);
}

TEST(Basic, Test3)
{
    Pangram pg;
    EXPECT_EQ(pg.CheckIfPangram(""), false);
}