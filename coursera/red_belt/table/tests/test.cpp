#include "table.h"
#include "gtest/gtest.h"

#include <sstream>

TEST( TestTable, ConstructTable )
{
  Table<int> t(1, 1);
  EXPECT_EQ(t.Size().first, 1u);
  EXPECT_EQ(t.Size().second, 1u);
}

TEST( TestTable, ConstructTable_LineNumberIsNull )
{
  Table<int> t(1, 0);
  EXPECT_EQ(t.Size().first, 0);
  EXPECT_EQ(t.Size().second, 0);
}

TEST( TestTable, AssignmentValueByIndex )
{
  Table<int> t(1, 1);
  t[0][0] = 42;
  EXPECT_EQ(t[0][0], 42);
}

TEST( TestTable, TableFillInByDefault )
{
  Table<int> t(2, 2);
  t[1][1] = 42;
  EXPECT_EQ(t[1][1], 42);
  EXPECT_EQ(t[0][0], 0);
}

TEST( TestTable, OperatorConst )
{
  Table<int> t(2, 2);
  t[1][1] = 42;
  std::ostringstream os;
  os << t[1][1];
  EXPECT_EQ(os.str(), "42");
}

TEST( TestTable, ResizeTable_SizeMoreThanPrevious )
{
  Table<int> t(1, 1);
  t.Resize(3, 4);
  EXPECT_EQ(t.Size().first, 3u);
  EXPECT_EQ(t.Size().second, 4u);
}

TEST( TestTable, ResizeTable_SizeMoreThanPrevious_TableFillInByDefault_SavingPreiousValues )
{
  Table<int> t(2, 2);
  t[1][1] = 42;
  t.Resize(3, 4);
  EXPECT_EQ(t[1][1], 42);
  EXPECT_EQ(t[2][2], 0);
  EXPECT_EQ(t[1][2], 0);
  EXPECT_EQ(t.Size().first, 3u);
  EXPECT_EQ(t.Size().second, 4u);
}

TEST( TestTable, ResizeTable_SizeLessThanPrevious_TableFillInByDefault_SavingPreiousValues )
{
  Table<int> t(7, 9);
  t[1][1] = 42;
  t.Resize(2, 2);
  EXPECT_EQ(t[1][1], 42);
  EXPECT_EQ(t[0][0], 0);
  EXPECT_EQ(t.Size().first, 2u);
  EXPECT_EQ(t.Size().second, 2u);
}

TEST( TestTable, ResizeTable_LessLinesMoreColumns )
{
  Table<int> t(3, 3);
  t[1][1] = 42;
  t.Resize(2, 4);
  EXPECT_EQ(t[1][1], 42);
  EXPECT_EQ(t[1][3], 0);
  EXPECT_EQ(t.Size().first, 2u);
  EXPECT_EQ(t.Size().second, 4u);
}

TEST( TestTable, ResizeTable_MoreLinesLessColumns )
{
  Table<int> t(3, 3);
  t[1][1] = 42;
  t.Resize(4, 2);
  EXPECT_EQ(t.Size().first, 4u);
  EXPECT_EQ(t.Size().second, 2u);
  EXPECT_EQ(t[1][1], 42);
  EXPECT_EQ(t[3][1], 0);
}

TEST( TestTable, ResizeTable_FirstTableIsNull )
{
  Table<int> t(1, 0);
  t.Resize(2, 4);
  EXPECT_EQ(t[1][3], 0);
  EXPECT_EQ(t.Size().first, 2u);
  EXPECT_EQ(t.Size().second, 4u);
}


