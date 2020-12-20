#include "gtest/gtest.h"
#include "max.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>


TEST( TestUniqueMax, ExpectLastElement )
{
  auto IsEven = [](int x) 
  {
    return x % 2 == 0;
  };

  const std::list<int> hill{2, 4, 8, 9, 6, 4, 2};
  auto max_iterator = hill.begin();
  std::advance(max_iterator, 2);

  std::vector<int> numbers(10);
  std::iota(numbers.begin(), numbers.end(), 1);

  EXPECT_EQ( max_element_if(numbers.begin(), numbers.end(), IsEven), --numbers.end()) ;
  EXPECT_EQ( max_element_if(hill.begin(), hill.end(), IsEven), max_iterator );
}

TEST( TestSeveralMax, Test2 )
{
  struct IsCapitalized 
  {
    bool operator()(const std::string &s) 
    {
      return !s.empty() && isupper(s.front());
    }
  };

  const std::forward_list<std::string> text 
                    { "One", "two", "Three", "One", "Two","Three", "one", "Two", "three" };
  auto max_iterator = text.begin();
  std::advance(max_iterator, 4);
  EXPECT_EQ( max_element_if(text.begin(), text.end(), IsCapitalized()), max_iterator );
}

TEST( TestNoMax, Test3 ) 
{
  const std::vector<int> empty;
  const std::string str = "Non-empty string";

  auto AlwaysTrue = [](int) 
  {
    return true;
  };
  EXPECT_EQ( max_element_if(empty.begin(), empty.end(), AlwaysTrue), empty.end() );
  
  auto AlwaysFalse = [](char) 
  {
    return false;
  };
  EXPECT_EQ( max_element_if(str.begin(), str.end(), AlwaysFalse), str.end() );
}
