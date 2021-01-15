#include "gtest/gtest.h"
#include "swap_sort_copy.h"
#include <string>
#include <vector>

TEST( Swap, Test )
{
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  EXPECT_EQ(a, 2);
  EXPECT_EQ(b, 1);

  std::string h = "world";
  std::string w = "hello";
  Swap(&h, &w);
  EXPECT_EQ(h, "hello");
  EXPECT_EQ(w, "world");

/*  int* pa = &a;
  int* pb = &b;
  Swap( pa, pb );
  EXPECT_EQ( pa, &b );
  EXPECT_EQ( pb, &a );  */
}

TEST( SortPointers, Test1 )
{
  int one = 1;
  int two = 2;
  int three = 3;

  std::vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  EXPECT_EQ(pointers.size(), 3u);
  EXPECT_EQ(*pointers[0], 1);
  EXPECT_EQ(*pointers[1], 2);
  EXPECT_EQ(*pointers[2], 3);
}

TEST( ReverseCopy, Test )
{
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) 
    source[i] = i + 1;
  
  ReversedCopy(source, count, dest);
  const std::vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(std::vector<int>(dest, dest + count), expected1);

  // Области памяти могут перекрываться
  ReversedCopy(source, count - 1, source + 1);
  const std::vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(std::vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}
