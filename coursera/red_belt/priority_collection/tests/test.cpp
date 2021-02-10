#include "gtest/gtest.h"
#include "priority_col.h"

#include <string>

class StringNonCopyable : public std::string 
{
public:
  using std::string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};


TEST( TestNoCopy, Test1 )
{
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);

  for (int i = 0; i < 2; ++i)
    strings.Promote(red_id);

  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    EXPECT_EQ(item.first, "red");
    EXPECT_EQ(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    EXPECT_EQ(item.first, "yellow");
    EXPECT_EQ(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    EXPECT_EQ(item.first, "white");
    EXPECT_EQ(item.second, 0);
  }
}

