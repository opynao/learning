#include "truncate.h"
#include "gtest/gtest.h"

TEST(Basic, Test1)
{
    std::string str{"Hello how are you Contestant"};
    Solution s;
    std::string result{"Hello how are you"};
    EXPECT_EQ(s.truncateSentence(str, 4), result);
}

TEST(Basic, Test2)
{
    std::string str{"What is the solution to this problem"};
    Solution s;
    std::string result{"What is the solution"};
    EXPECT_EQ(s.truncateSentence(str, 4), result);
}

TEST(Basic, Test3)
{
    std::string str{"chopper is not a tanuki"};
    Solution s;
    std::string result{"chopper is not a tanuki"};
    EXPECT_EQ(s.truncateSentence(str, 5), result);
}