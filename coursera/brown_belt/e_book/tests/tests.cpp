#include "gtest/gtest.h"
#include "parser.h"
#include <sstream>

TEST(Basic, Test1)
{
    std::istringstream iss{"12\nCHEER 5\nREAD 1 10\nCHEER 1\nREAD 2 5\n"
                           "READ 3 7\nCHEER 2\nCHEER 3\nREAD 3 10\nCHEER 3"
                           "\nREAD 3 11\nCHEER 3\nCHEER 1"};
    std::ostringstream oss;
    Parser parser(iss, oss);
    std::string result{"0\n1\n0\n0.5\n0.5\n1\n0.5\n"};
    EXPECT_EQ(oss.str(), result);
}