#include "paginator.h"
#include "gtest/gtest.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class PaginatorTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    v.resize( 15, 1 );
  }
  std::vector<int> v;
};

TEST_F( PaginatorTest, testConstructor )
{
  const auto upPaginator = std::make_unique<Paginator<std::vector<int>::iterator>>(v.begin(), v.end(), 5);
  EXPECT_NE( upPaginator, nullptr );
}


TEST_F( PaginatorTest, TestPageCounts )
{
  EXPECT_EQ(Paginate(v, 1).size(), v.size());
  EXPECT_EQ(Paginate(v, 3).size(), 5u);
  EXPECT_EQ(Paginate(v, 5).size(), 3u);
  EXPECT_EQ(Paginate(v, 4).size(), 4u);
  EXPECT_EQ(Paginate(v, 15).size(), 1u);
  EXPECT_EQ(Paginate(v, 150).size(), 1u);
  EXPECT_EQ(Paginate(v, 14).size(), 2u);
}

 
TEST_F( PaginatorTest, TestLooping ) 
{
  std::iota(std::begin(v), std::end(v), 1);

  Paginator<std::vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  std::ostringstream os;
  for (const auto& page : paginate_v) 
  {
    for (int x : page) 
      os << x << ' ';
    os << '\n';
  }

  EXPECT_EQ(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}


TEST( Paginator, TestModification ) 
{
  std::vector<std::string> vs = {"one", "two", "three", "four", "five"};
  for (auto page : Paginate(vs, 2)) 
  {
    for (auto& word : page) 
      word[0] = std::toupper(word[0]);
  }

  const std::vector<std::string> expected = {"One", "Two", "Three", "Four", "Five"};
  EXPECT_EQ(vs, expected);
}


TEST( Paginator, TestPageSizes )
{
  std::string letters(26, ' ');

  Paginator letters_pagination(letters.begin(), letters.end(), 11);
  std::vector<size_t> page_sizes;
  for (const auto& page : letters_pagination) 
    page_sizes.push_back(page.size());

  const std::vector<size_t> expected = {11, 11, 4};
  EXPECT_EQ(page_sizes, expected);
}

TEST( Paginator, TestConstContainer ) 
{
  const std::string letters = "abcdefghijklmnopqrstuvwxyz";

  std::vector<std::string> pages;
  for (const auto& page : Paginate(letters, 10)) 
    pages.push_back(std::string(page.begin(), page.end()));

  const std::vector<std::string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
  EXPECT_EQ(pages, expected);
}

TEST( Paginator, TestPagePagination ) 
{
  std::vector<int> v(22);
  std::iota(std::begin(v), std::end(v), 1);

  std::vector<std::vector<int>> lines;
  for (const auto& split_by_9 : Paginate(v, 9)) 
  {
    for (const auto& split_by_4 : Paginate(split_by_9, 4)) 
    {
      lines.push_back({});
      for (int item : split_by_4) 
        lines.back().push_back(item);
    }
  }

  const std::vector<std::vector<int>> expected = 
  {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9},
      {10, 11, 12, 13},
      {14, 15, 16, 17},
      {18},
      {19, 20, 21, 22}
  };
  EXPECT_EQ(lines, expected);
}
