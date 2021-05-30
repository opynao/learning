#include "gtest/gtest.h"
#include "parser.h"
#include "utils.h"

#include <sstream>
#include <string>

TEST(Basic, Test1)
{
    std::istringstream iss{"4\nya.ru\nmaps.me\nm.ya.ru\ncom\n"
                           "7\nya.ru\nya.com\nm.maps.me\nmoscow.m.ya.ru\nmaps.com\nmaps.ru\nya.ya\n"};
    std::ostringstream oss;
    std::string result{"Bad\nBad\nBad\nBad\nBad\nGood\nGood\n"};
    Parser parse(iss, oss);

    EXPECT_EQ(oss.str(), result);
}

TEST(Basic, Test2)
{
    std::istringstream iss{"2\nb.c\na.b.c\n"
                           "1\nd.b.c\n"};
    std::ostringstream oss;
    std::string result{"Bad\n"};
    Parser parse(iss, oss);

    EXPECT_EQ(oss.str(), result);
}