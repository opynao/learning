#include "paginator.h"
#include "gtest/gtest.h"

#include <numeric>
#include <vector>
#include <string>
#include <list>

class IteratorRangeTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    v.resize( 10, 1 );
    std::iota(std::begin(v), std::end(v), 1);
  }
  std::vector<int> v;
  std::ostringstream os;
};


TEST_F( IteratorRangeTest, TestLooping )
{
  IteratorRange<std::vector<int>::iterator> itRange (v.begin(), v.end());
  for( const auto& elem : itRange )
    os << elem << " ";
  EXPECT_EQ( os.str(), "1 2 3 4 5 6 7 8 9 10 " );
}

TEST_F( IteratorRangeTest, TestLooping1 )
{
  IteratorRange<std::vector<int>::iterator> itRange (v.begin(), (v.begin() + 5));
  for( const auto& elem : itRange )
    os << elem << " ";
  EXPECT_EQ( os.str(), "1 2 3 4 5 " );
}

TEST_F( IteratorRangeTest, sizeVector )
{
  IteratorRange<std::vector<int>::iterator> itRange (v.begin(), v.end());
  EXPECT_EQ( itRange.size(), 10 );
}

TEST( IteratorRange, sizeMap )
{
  std::map< std::string, int > m 
  { { "a", 1 },
    { "b", 2 },
    { "c", 3 }
  };
  IteratorRange<std::map< std::string, int >::iterator> itRange (m.begin(), m.end());
  EXPECT_EQ( itRange.size(), 3 );
}

TEST( IteratorRange, sizeList )
{
  std::list< int > l { 1, 3, 15, 2 };
  IteratorRange<std::list< int >::iterator> itRange (l.begin(), l.end());
  EXPECT_EQ( itRange.size(), 4 );
}
