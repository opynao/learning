#include "airline_ticket.h"
#include <string>
#include <sstream>
#include <istream>
#include <tuple>

#define UPDATE_FIELD(ticket, field, values) \
  if (values.find(#field) != values.end()) { \
    std::istringstream is(values.find(#field)->second);      \
    is >> ticket.field; }                   \

bool operator==(const Date& lhs, const Date& rhs)
{
  return std::tie( lhs.year, lhs.month, lhs.day ) == std::tie ( rhs.year, rhs.month, rhs.day );
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

int main()
{
    return 0;
}
