#include <vector>
#include <iostream>
#include <tuple>
#include "airline_ticket.h"

bool operator < ( const Date& lhs, const Date& rhs )
{
  return std::tie( lhs.year, lhs.month, lhs.day ) < std::tie ( rhs.year, rhs.month, rhs.day );
}

bool operator==(const Date& lhs, const Date& rhs)
{
  return std::tie( lhs.year, lhs.month, lhs.day ) == std::tie ( rhs.year, rhs.month, rhs.day );
}

bool operator<(const Time& lhs, const Time& rhs)
{
  return std::tie( lhs.hours, lhs.minutes ) < std::tie( rhs.hours, rhs.minutes );
}

bool operator==(const Time& lhs, const Time& rhs)
{
  return std::tie( lhs.hours, lhs.minutes ) == std::tie( rhs.hours, rhs.minutes );
}


std::istream& operator >>(std::istream& is, Date& date)
{
  is >> date.year;
  is.get();
  is >> date.month;
  is.get();
  is >> date.day;
  return is;
}

std::istream& operator >>(std::istream& is, Time& time)
{
  is >> time.hours;
  is.get();
  is >> time.minutes;
  return is;
}

