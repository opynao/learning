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
  std::ostringstream oss;
};


TEST_F( RemoveIfTest, Remove_By_Date )
{
    std::istringstream is ("date == 2017-03-08");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    EXPECT_EQ( 1, db.RemoveIf(predicate) );
}

TEST_F( RemoveIfTest, Remove_By_Date2 )
{
    std::istringstream is ("date < 2017-03-08");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    EXPECT_EQ( 2, db.RemoveIf(predicate) );
    db.Print(oss);
    EXPECT_EQ( oss.str(), "2017-03-08 Holiday\n");
}

TEST_F( RemoveIfTest, RemoveIf_Delete_All_Events )
{
    std::istringstream is ("");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    EXPECT_EQ( db.RemoveIf(predicate), 3 );
}


TEST_F( RemoveIfTest, Remove_Nothing )
{
    std::istringstream is  (R"(event == "something")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    EXPECT_EQ( db.RemoveIf(predicate), 0 );
}    

TEST_F( RemoveIfTest, Remove_By_Event )
{
    std::istringstream is  (R"(event == "New Year")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    EXPECT_EQ( db.RemoveIf(predicate), 1 );
    db.Print(oss);
    EXPECT_EQ("2017-01-01 Holiday\n2017-03-08 Holiday\n", oss.str());
}

TEST_F( RemoveIfTest, Removing_Event_and_Than_Adding_Removed_Event )
{
    std::istringstream is  (R"(event == "New Year")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event){ return condition->Evaluate(date, event);};
    EXPECT_EQ( db.RemoveIf(predicate), 1 );
    db.Print(oss);
    EXPECT_EQ("2017-01-01 Holiday\n2017-03-08 Holiday\n", oss.str());
    db.Add({2017,1,1},"New Year");
    oss.str("");   
    db.Print(oss);
    EXPECT_EQ("2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n", oss.str());
}


