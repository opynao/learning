#include "gtest/gtest.h"
#include "print.h"
#include <sstream>

class PrintTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }
  std::ostringstream output;
};

TEST_F( PrintTest, Correct_Output )
{
  PRINT_VALUES(output, 5, "red belt");
  EXPECT_EQ(output.str(), "5\nred belt\n");
}

TEST_F( PrintTest, Correct_Output1 )
{
  PRINT_VALUES(output, 5, "");
  EXPECT_EQ(output.str(), "5\n\n");
}

TEST_F( PrintTest, Correct_Output2 )
{
  bool arg = true;
  if( arg )
    PRINT_VALUES(output, 5, "");
  else 
    PRINT_VALUES(output, 5, "");
  EXPECT_EQ(output.str(), "5\n\n");
}

TEST_F( PrintTest, Correct_Output3 )
{
  for( int i = 0; i != 2; ++i )
    PRINT_VALUES(output, 5, "1");
  EXPECT_EQ(output.str(), "5\n1\n5\n1\n");
}
