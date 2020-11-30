#include "condition_parser.h"
#include "node.h"
#include "condition_parser.h"
#include "parse_date_event.h"
#include "date.h"

#include <sstream>
#include "gtest/gtest.h"


TEST( ParseCondition, DateComparisonNode )
{
	std::istringstream is("date != 2017-11-18");
    std::istringstream date_iss1("2017-11-17");
    std::istringstream date_iss2("2017-11-18");
    auto root = ParseCondition(is);
    const Date date1 = ParseDate(date_iss1);
    const Date date2 = ParseDate(date_iss2);
    EXPECT_EQ( root->Evaluate(date1,""), true );
    EXPECT_EQ( !root->Evaluate(date2, ""), true);
}

TEST( ParseCondition, EventComparisonNode )
{
    std::istringstream is(R"(event == "sport event")");
    auto root = ParseCondition(is);
    EXPECT_EQ( root->Evaluate({},"sport event"), true );
    EXPECT_EQ( !root->Evaluate({}, "holiday"), true);
}

TEST( ParseCondition, LogicalOperationNode )
{
  std::istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
  std::shared_ptr<Node> root = ParseCondition(is);
  Date date;
  std::vector<std::string> vTrue {"2017-1-1","2017-6-30","2017-3-1"};
  for( auto& item : vTrue )
  {
    std::istringstream iss(item);
    date = ParseDate(iss);
    EXPECT_EQ( root->Evaluate( date, ""), true);
  }
}

TEST( ParseCondition, LogicalOperationNode2 )
{
  std::istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
  std::shared_ptr<Node> root = ParseCondition(is);
  Date date;
  std::vector<std::string> vFalse {"2016-12-31","20-6-30","2017-8-1"};
  for( auto& item : vFalse )
  {
    std::istringstream iss(item);
    date = ParseDate(iss);
    EXPECT_EQ( !root->Evaluate( date, ""), true);
  }
}

/*  {
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
    Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
    Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
  }
  {
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
    Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
    Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
  }
  {
    istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
  }
  {
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
  }
  {
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
    Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
    Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
  }
}*/
