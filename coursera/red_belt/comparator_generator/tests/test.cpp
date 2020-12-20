#include "gtest/gtest.h"
#include "airline_ticket.h"

#include <vector>
#include <algorithm>
#include <string>

TEST( TestSortBy, Test1 )
{
  std::vector<AirlineTicket> tixs = 
  {
    {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  std::sort(begin(tixs), end(tixs), SORT_BY(price));
  EXPECT_EQ(tixs.front().price, 1200);
  EXPECT_EQ(tixs.back().price, 9000);

  std::sort(begin(tixs), end(tixs), SORT_BY(from));
  EXPECT_EQ(tixs.front().from, "AER");
  EXPECT_EQ(tixs.back().from, "VKO");

  std::sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  EXPECT_EQ(tixs.front().arrival_date, (Date{2018, 2, 9}));
  EXPECT_EQ(tixs.back().arrival_date, (Date{2018, 3, 5}));
}


TEST( TestUpdate, Test2 )
{
  using namespace std;
  AirlineTicket t;
  t.price = 0;

  const std::map<string, string> updates1 = 
    {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
    };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  EXPECT_EQ(t.departure_date, (Date{2018, 2, 28}));
  EXPECT_EQ(t.departure_time, (Time{17, 40}));
  EXPECT_EQ(t.price, 0);

  const std::map<string, string> updates2 = 
    {
      {"price", "12550"},
      {"arrival_time", "20:33"},
    };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  EXPECT_EQ(t.departure_date, (Date{2018, 2, 28}));
  EXPECT_EQ(t.departure_time, (Time{17, 40}));
  EXPECT_EQ(t.price, 12550);
  EXPECT_EQ(t.arrival_time, (Time{20, 33}));
}


