#include "parser.h"
#include "gtest/gtest.h"

TEST( Parser, Test1 )
{
    std::istringstream is ("8\n1 1 2 2 6 9 9 15\n4\n1 4 9 15\n");
    std::ostringstream os;
    Parser pr;
    pr.Parse(is);
    Print( pr, os );
    EXPECT_EQ( os.str(), "Yes 1\nNo 5\nYes 6\nYes 8\n" );
}
