#include "Common.h"
#include "gtest/gtest.h"
#include <sstream>

using namespace std;

string Print(const Expression *e)
{
    if (!e)
        return "Null expression provided";

    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

TEST(Basic, Test1)
{
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    EXPECT_EQ(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    EXPECT_EQ(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    EXPECT_EQ(Print(e1.get()), "Null expression provided");

    ExpressionPtr e3 = Value(5);
    EXPECT_EQ(Print(e3.get()), "5 = 5");
}
