#include "gtest/gtest.h"

#include "condition_parser.h"
#include "node.h"
#include "condition_parser.h"
#include "parse_date_event.h"
#include "date.h"
#include "database.h"


class RemoveIfTest : public ::testing::Test
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


TEST_F( RemoveIfTest, RemoveIf_Delete_One_Event_In_Database )
{
    std::istringstream is ("date == 2017-03-08");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    int count = db.RemoveIf(predicate);
	int result = 1;
    EXPECT_EQ( count, result );
}

TEST_F( RemoveIfTest, RemoveIf_Delete_Null_Events_In_Database )
{
    std::istringstream is ("date < 201-03-08");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    int count = db.RemoveIf(predicate);
	int result = 0;
    EXPECT_EQ( count, result );
}

TEST_F( RemoveIfTest, RemoveIf_Delete_All_Events )
{
    std::istringstream is ("");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    int count = db.RemoveIf(predicate);
	int result = 3;
    EXPECT_EQ( count, result );
}


