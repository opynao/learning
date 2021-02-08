#include "gtest/gtest.h"
#include "group_strings.h"

#include <vector>
#include <string>
#include <algorithm>

TEST( TestGroupingABC, Test1 )
{
  std::vector<std::string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  EXPECT_EQ(groups.size(), 2);
  std::sort( std::begin(groups), std::end(groups) );  // Порядок групп не имеет значения
  EXPECT_EQ(groups[0], std::vector<std::string>({"caab", "abc", "bacc"}));
  EXPECT_EQ(groups[1], std::vector<std::string>({"cccc", "c"}));
}

TEST( TestGroupingReal, Test2 )
{
  std::vector<std::string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  EXPECT_EQ(groups.size(), 4);
  std::sort( std::begin(groups), std::end(groups));  // Порядок групп не имеет значения
  EXPECT_EQ(groups[0], std::vector<std::string>({"laptop", "paloalto"}));
  EXPECT_EQ(groups[1], std::vector<std::string>({"law", "wall", "awl"}));
  EXPECT_EQ(groups[2], std::vector<std::string>({"port"}));
  EXPECT_EQ(groups[3], std::vector<std::string>({"top", "pot"}));
}

