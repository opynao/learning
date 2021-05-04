#include "animals.h"
#include "gtest/gtest.h"
#include "zoo.h"
#include <sstream>

using namespace std;

TEST(Basic, Zoo)
{
    istringstream input("Tiger Wolf Fox Tiger");
    ostringstream output;
    Process(CreateZoo(input), output);

    const string expected =
        "Rrrr\n"
        "Wooo\n"
        "Tyaf\n"
        "Rrrr\n";

    EXPECT_EQ(output.str(), expected);
}