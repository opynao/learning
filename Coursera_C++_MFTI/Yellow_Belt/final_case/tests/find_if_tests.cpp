#include "gtest/gtest.h"

#include "condition_parser.h"
#include "node.h"
#include "condition_parser.h"
#include "parse_date_event.h"
#include "date.h"
#include "database.h"


class FindIfTest : public ::testing::Test
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

TEST_F( FindIfTest, FindIf_Finds_One_Event_In_Database )
{
    std::istringstream is ("date == 2017-03-08");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    vEvents_t find_if_db { db.FindIf(predicate) };
    Event_t event {"Holiday"};
	vEvents_t result { { {Date ("2017-03-08")},{ event}} };
    EXPECT_EQ( find_if_db, result );
}

TEST_F( FindIfTest, FindIf_Finds_Null_Events_In_Database )
{
    std::istringstream is ("date < 201-03-08");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    vEvents_t find_if_db = db.FindIf(predicate);
	vEvents_t result {};
    EXPECT_EQ( find_if_db, result );
}

TEST_F( FindIfTest, FindIf_Finds_All_Events )
{
    std::istringstream is ("");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    vEvents_t find_if_db = db.FindIf(predicate);
	vEvents_t result {
                        { Date ("2017-01-01"),"New Year"},
                        { Date ("2017-01-01"),"Holiday"},
                        { Date ("2017-03-08"),"Holiday"}
                      };
    EXPECT_EQ( find_if_db, result );
}
