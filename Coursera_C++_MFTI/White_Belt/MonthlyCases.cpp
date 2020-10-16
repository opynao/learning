#include <memory>
#include <cassert>
#include <map>
#include <string>
#include <iostream>

using Day_t = size_t;
using Case_t = std::string;
using mmDayCase_t = std::multimap<Day_t, Case_t>;

class Calendar
{
public:
  void AddCase(const Day_t&, const Case_t&);
  void DumpCase(const Day_t&) const;
private:
  mmDayCase_t m_MonthCases{};
};

void Calendar::AddCase(const Day_t& day,const Case_t& dayCase) 
{
  m_MonthCases.insert(std::make_pair(day, dayCase));
}

void Calendar::DumpCase(const Day_t& day) const
{
/*  auto range = m_MonthCases.equal_range(day);
  std::cout << std::count(std::cbegin(m_MonthCases), std::cend(m_MonthCases), [Day_t & day]() {return m_MonthCases.first = day; });
  for (auto i = range.first; i != range.second; ++i)
  {
    std::cout << i->second << " ";
  }*/
}

void testCalendar_DefaultConstruct()
{
  const auto upCalendar = std::make_unique<Calendar>();
  assert(nullptr != upCalendar);
}

void testAddCase()
}

void testCalendar_DumpCase_ReturnZeroCases()
{
  const auto upCalendar = std::make_unique<Calendar>();
  assert("" == upCalendar->DumpCase(1));
}

int main()
{
  testCalendar_DefaultConstruct();
  testAddCase();
  testCalendar_DumpCase_ReturnZeroCases()
  return 0;
}
