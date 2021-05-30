#include "gtest/gtest.h"
#include "SquareRoot.h"

TEST(testMath, myTest)
{
    EXPECT_EQ(10000, SquareRoot(100));	
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


