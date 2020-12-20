#pragma once

#include <string>
#include <sstream>

struct AirlineTicket;

#define SORT_BY(field)                                   \
[](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
  return lhs.field < rhs.field;                          \
} \

#define UPDATE_FIELD(ticket, field, values) \
  if (values.find(#field) != values.end()) { \
    std::istringstream is(values.find(#field)->second);      \
    is >> ticket.field; }                   \

struct Date 
{
  int year;
  int month;
  int day;
};

struct Time 
{
  int hours;
  int minutes;
};

struct AirlineTicket 
{
  std::string from;
  std::string to;
  std::string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};

bool operator<(const Date& lhs, const Date& rhs);

bool operator<(const Time& lhs, const Time& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator==(const Time& lhs, const Time& rhs);

std::istream& operator >>(std::istream& is, Date& date);

std::istream& operator >>(std::istream& is, Time& time);
