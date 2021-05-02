#include "gtest/gtest.h"
#include "command.h"
#include <sstream>

TEST(Basic, Test1)
{
    LOGF;
    std::istringstream iss{
        "11\nIvan 25 1000 M\nOlga 30 623 W\nSergey 24 825 M\n"
        "Maria 42 1254 W\nMikhail 15 215 M\nOleg 18 230 M\nDenis 53 8965 M\n"
        "Maxim 37 9050 M\nIvan 47 19050 M\nIvan 17 50 M\nOlga 23 550 W\n"
        "AGE 18\nAGE 25\nWEALTHY 5\nPOPULAR_NAME M\n "};
    std::ostringstream oss;
    CommandHandler(iss, oss);
    LOGF;
    std::string result{"There are 9 adult people for maturity age 18\n"
                       "There are 6 adult people for maturity age 25\n"
                       "Top-5 people have total income 39319\n"
                       "Most popular name among people of gender M is Ivan\n"};
    LOGF;
    EXPECT_EQ(oss.str(), result);
}

TEST(Basic, Test2)
{
    std::istringstream iss{
        "11\nIvan 25 1000 M\nOlga 30 623 M\nSergey 24 825 M\n"
        "Maria 42 1254 M\nMikhail 15 215 M\nOleg 18 230 M\nDenis 53 8965 M\n"
        "Maxim 37 9050 M\nIvan 47 19050 M\nIvan 17 50 M\nOlga 23 550 M\n"
        "AGE 0\nAGE 55\nWEALTHY 1\nPOPULAR_NAME W\n"};
    std::ostringstream oss;
    CommandHandler(iss, oss);
    std::string result{"There are 11 adult people for maturity age 0\n"
                       "There are 0 adult people for maturity age 55\n"
                       "Top-1 people have total income 19050\n"
                       "No people of gender W\n"};
    EXPECT_EQ(oss.str(), result);
}

TEST(Basic, Test3)
{
    std::istringstream iss{
        "4\nIvan 10 1000 M\nOlga 40 623 M\nSergey 60 825 M\n"
        "Maria 100 1254 M\nAGE 15\nAGE 45\nAGE 59\nAGE 90\n"};
    std::ostringstream oss;
    CommandHandler(iss, oss);
    std::string result{"There are 3 adult people for maturity age 15\n"
                       "There are 2 adult people for maturity age 45\n"
                       "There are 2 adult people for maturity age 59\n"
                       "There are 1 adult people for maturity age 90\n"};
    EXPECT_EQ(oss.str(), result);
}