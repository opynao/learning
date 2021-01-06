#include "parser.h"
#include "profile.h"
#include "gtest/gtest.h"
#include <sstream>
#include <fstream>

TEST( Parser, Test1)
{
    std::istringstream is("2 2\n3 1 5 4\n5 1 2 8 9 3\n0 1\n1 3\n");
    std::ostringstream os;
    Parser pr;
    {
        LOG_DURATION("Input");
        pr.Parse(is);
    }
    {
        LOG_DURATION("Output");
        Print( pr, os );
    }
    EXPECT_EQ( os.str(), "5\n9\n" );
}

TEST( Parser, Test2 )
{
    std::ifstream file("/home/vika/learning/coursera/red_belt/variable_arrays/input04.txt");
    std::ostringstream os;
    Parser pr;
    {
        LOG_DURATION("Input");
        pr.Parse(file);
    }
    {
        LOG_DURATION("Output");
        Print( pr, os );
    }
}
