#include "gtest/gtest.h"

#include "condition_parser.h"
#include "node.h"
#include "condition_parser.h"
#include "parse_date_event.h"
#include "date.h"
#include "database.h"


class AddTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
     for(const auto& item : vInput)
      {
          std::istringstream iss (item.second);
          db.Add(Date (item.first), ParseEvent(iss));
      }
  }
  Database db;
  std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","New Year"},{"2017-03-08","Holiday"},{"2017-01-01","Holiday"}};
};

TEST_F( AddTest, Adding_Three_Events_To_Database )
{
  EXPECT_EQ( db.GetDatabaseSize(), 2 );
}

TEST_F( AddTest, Ignoring_Adding_Two_Events_In_One_Day )
{
  db.Add( Date ("2017-03-08"), "Holiday" );
  EXPECT_EQ( db.GetEventsCountByDate(Date ("2017-03-08")), 1 );
}

TEST( Add, Ignoring_Adding_Some_Equal_Events_In_One_Date )
{
  Database db;
  std::istringstream is("01.03 1");
  Event_t event = ParseEvent(is);
  std::istringstream is1("01.03 2");
  Event_t event1 = ParseEvent(is1);
  db.Add( Date ("2017-03-01"), event );
  db.Add( Date ("2017-03-01"), event1 );
  db.Add( Date ("2017-03-01"), event );
  db.Add( Date ("2017-03-01"), event );
  db.Add( Date ("2017-03-01"), event1 );
  EXPECT_EQ( db.GetEventsCountByDate(Date ("2017-03-01")), 2 );
  std::istringstream is_cond ("date == 2017-03-01");
  auto condition = ParseCondition(is_cond);
  auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
  vEvents_t find_if_db { db.FindIf(predicate) };
  vEvents_t result { { Date ("2017-03-01"),"01.03 1"}, { Date ("2017-03-01"),"01.03 2"}};
  EXPECT_EQ( find_if_db, result );
}

TEST( Add, Straight_Ordering)
{
  Database db;
  db.Add(Date (2017, 1, 1), "new year");
  db.Add(Date (2017, 1, 7), "xmas");
  std::ostringstream out;
  db.Print(out);
  EXPECT_EQ("2017-01-01 new year\n2017-01-07 xmas\n", out.str()); 
}

TEST( Add, Several_In_One_Day )
{
  Database db;
  db.Add(Date (2017, 1, 1), "new year");
  db.Add(Date (2017, 1, 1), "holiday");
  std::ostringstream out;
  db.Print(out);
  EXPECT_EQ("2017-01-01 new year\n2017-01-01 holiday\n", out.str());
}

TEST( Add, Reverse_Ordering )
{
  Database db;
  db.Add(Date (2017, 1, 7), "xmas");
  db.Add(Date (2017, 1, 1), "new year");
  std::ostringstream out;
  db.Print(out);
  EXPECT_EQ("2017-01-01 new year\n2017-01-07 xmas\n", out.str()); 
}

TEST( Add, Uniq_Adding)
{
  Database db;
  db.Add(Date (2017, 1, 1), "new year");
  db.Add(Date (2017, 1, 1), "new year");
  db.Add(Date (2017, 1, 1), "xmas");
  db.Add(Date (2017, 1, 1), "new year");
  std::ostringstream out;
  db.Print(out);
  EXPECT_EQ("2017-01-01 new year\n2017-01-01 xmas\n", out.str());
}

TEST( Add, Remove_by_date)
{
    Database db;
    db.Add({2017, 1, 1}, "new year");
    db.Add({2017, 1, 7}, "xmas");
    db.Add({2017, 1, 7}, "party");
    db.Add({2017, 1, 7}, "pie");
    std::ostringstream out;
    db.Print(out);
    EXPECT_EQ("2017-01-01 new year\n2017-01-07 xmas\n2017-01-07 party\n2017-01-07 pie\n", out.str());
}
