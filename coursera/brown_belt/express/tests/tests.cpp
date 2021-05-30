#include "parser.h"
#include "gtest/gtest.h"
#include <string>

TEST(Basic, Test1)
{
    std::istringstream iss{"7\nADD -2 5\nADD 10 4\nADD 5 8\nGO 4 10\nGO 4 -2\nGO 5 0\nGO 5 100\n"};
    std::ostringstream oss;
    Parser parser(iss, oss);
    std::string result{"0\n6\n2\n92\n"};
    EXPECT_EQ(oss.str(), result);
}