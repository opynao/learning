#include <set>
#include <iterator>
#include "gtest/gtest.h"
#include "find_nearest_element.h"

TEST( testFindNearestElement, EmptySet )
{
  std::set<int> empty_set;
  EXPECT_EQ(FindNearestElement(empty_set, 8), std::cend(empty_set));
}

TEST( testFindNearestElement, SetComposedFromOneElement )
{
  std::set<int> s {10};
  EXPECT_EQ(*FindNearestElement(s, 8), 10);
}

TEST( testFindNearestElement, SetContainsBorder )
{
  std::set<int> s {1,10};
  EXPECT_EQ(*FindNearestElement(s, 10), 10);
}

TEST( testFindNearestElement, BorderLessThanFirstElement )
{
  std::set<int> s {1,10};
  EXPECT_EQ(*FindNearestElement(s, 0), 1);
}

TEST( testFindNearestElement, BorderMoreThanLastElement )
{
  std::set<int> s {1,10};
  EXPECT_EQ(*FindNearestElement(s, 12), 10);
}

TEST( testFindNearestElement, BorderBetweenNumbersInSet )
{
  std::set<int> s {1,10};
  EXPECT_EQ(*FindNearestElement(s, 6), 10);
}

TEST( testFindNearestElement, BorderBetweenNumbersInSetReturnSmallest )
{
  std::set<int> s {0,10};
  EXPECT_EQ(*FindNearestElement(s, 5), 0);
}

TEST( testFindNearestElement, AcceptanceTest )
{
  std::set<int> numbers = {1, 4, 6};
  EXPECT_EQ(*FindNearestElement(numbers, 0), 1);
  EXPECT_EQ(*FindNearestElement(numbers, 3), 4);
  EXPECT_EQ(*FindNearestElement(numbers, 5), 4);
  EXPECT_EQ(*FindNearestElement(numbers, 6), 6);
  EXPECT_EQ(*FindNearestElement(numbers, 100), 6);      
  std::set<int> empty_set;
  EXPECT_EQ(FindNearestElement(empty_set, 8), std::cend(empty_set));
}


int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
