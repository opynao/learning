#include "student.h"
#include "gtest/gtest.h"

#include <vector>
#include <algorithm>

TEST( TestComparison, test1 )
{
  Student newbie {
    "Ivan", "Ivanov", {
      {"c++", 1.0},
      {"algorithms", 3.0}
    },
    2.0
  };

  Student cpp_expert {
    "Petr", "Petrov", {
      {"c++", 9.5},
      {"algorithms", 6.0}
    },
    7.75
  };

  Student guru {
    "Sidor", "Sidorov", {
      {"c++", 10.0},
      {"algorithms", 10.0}
    },
    10.0
  };
  EXPECT_EQ(Compare(guru, newbie), true);
  EXPECT_EQ(Compare(guru, cpp_expert), true);
  EXPECT_EQ(!Compare(newbie, cpp_expert), true);
}

TEST( TestSorting, test2 )
{
  std::vector<Student> students {
    {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
    {"Semen", "Semenov", {{"maths", 4.}}, 4.},
    {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
    {"Petr", "Petrov", {{"maths", 3.}}, 3.},
    {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
  };

  std::sort(students.begin(), students.end(), Compare);

  EXPECT_EQ(std::is_sorted(students.begin(), students.end(), [](Student first, Student second) { return first.Less(second); }), true );
}


