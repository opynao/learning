#include "simple_vector.h"
#include "gtest/gtest.h"

#include <numeric>
#include <vector>
#include <tuple>


TEST( TestCopyAssignment, Test1 )
{
  SimpleVector<int> numbers(10);
  std::iota( numbers.begin(), numbers.end(), 1 );
  SimpleVector<int> dest;
  EXPECT_EQ(dest.Size(), 0u);
  dest = numbers;
  EXPECT_EQ( dest.Size(), numbers.Size() );
  EXPECT_GE( dest.Capacity(), dest.Size() );
  EXPECT_EQ( std::equal(dest.begin(), dest.end(), numbers.begin()), true );
}
/*
TEST( TestCopyAssignment, Test2 )
{
  SimpleVector< MyClass > numbers(5);
  for( size_t i = 0; i != numbers.Size(); ++i )
  {
    MyClass m;
    numbers.PushBack( m );
  }
  SimpleVector< MyClass > res;
  res = numbers;
  EXPECT_EQ( res.Size(), numbers.Size() );
}*/
