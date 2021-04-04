#include "gtest/gtest.h"
#include "calculate.h"
#include "generate.h"
#include "profile.h"

#include <vector>

TEST( CalculateMatrixSum, BasicTest )
{
  const std::vector< std::vector< int > > matrix = 
  {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  EXPECT_EQ( CalculateMatrixSum(matrix), 136 );
}

TEST( Duration, Test1 )
{
  auto matrix = GenerateMatrix( 9000 );
  {
    LOG_DURATION("multiply thread");
    CalculateMatrixSum(matrix);
  }
}
