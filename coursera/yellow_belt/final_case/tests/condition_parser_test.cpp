#include "condition_parser.h"
#include "node.h"
#include "condition_parser.h"
#include "parse_date_event.h"
#include "date.h"
#include "database.h"

#include <sstream>
#include "gtest/gtest.h"


TEST( ParseCondition, DateComparisonNode )
{
	std::istringstream is("date != 2017-11-18");
    auto root = ParseCondition(is);
    EXPECT_EQ( root->Evaluate(Date ("2017-11-17"),""), true );
    EXPECT_EQ( !root->Evaluate(Date ("2017-11-18"), ""), true);
}

TEST( ParseCondition, EventComparisonNode )
{
    std::istringstream is(R"(event == "sport event")");
    auto root = ParseCondition(is);
    EXPECT_EQ( root->Evaluate({},"sport event"), true );
    EXPECT_EQ( !root->Evaluate({}, "holiday"), true);
}

TEST( ParseCondition, LogicalOperationNode_TwoDateComparisonNode )
{
  std::istringstream is("date >= 2016-01-01 AND date < 2017-07-01");
  std::shared_ptr<Node> root = ParseCondition(is);
  std::vector<std::string> vDates { "2017-1-1" , "2017-6-30" , "2017-3-1" };
  for( auto& item : vDates )
    EXPECT_EQ( root->Evaluate( Date (item), ""), true);
}

TEST( ParseCondition, LogicalOperationNode_TwoDateComparisonNode2 )
{
  std::istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
  std::shared_ptr<Node> root = ParseCondition(is);
  std::vector<std::string> vDates {"2016-12-31","20-6-30","2017-8-1"};
  for( auto& item : vDates )
    EXPECT_EQ( !root->Evaluate( Date (item), ""), true);
}

TEST( ParseCondition, LogicalOperationNode_TwoEventComparisonNode )
{
  std::istringstream is(R"(event != "sport event" AND event != "Wednesday")");
  std::shared_ptr<Node> root = ParseCondition(is);
  std::string date {"2017-11-17"};
  EXPECT_EQ( root->Evaluate( Date (date), "holiday"), true);
  EXPECT_EQ( root->Evaluate( Date (date), "sport event"), false);
  EXPECT_EQ( !root->Evaluate( Date (date), "Wednesday"), true);
}

TEST( ParseCondition, LogicalOperationNode_Date_and_Event )
{
  std::istringstream is(R"(event == "holiday AND date == 2017-11-18")");
  std::shared_ptr<Node> root = ParseCondition(is);
  EXPECT_EQ( !root->Evaluate( Date ("2017-11-18"), "holiday"), true);
  EXPECT_EQ( !root->Evaluate( Date ("2017-11-18"), "work day"), true);
  EXPECT_EQ( root->Evaluate( Date ("2017-11-18"), "holiday AND date == 2017-11-18"), true);
}

TEST( ParseCondition, ComplexLogicalOperationNode )
{
  std::istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
  std::shared_ptr<Node> root = ParseCondition(is);
  EXPECT_EQ( !root->Evaluate( Date ("2016-1-1"), "holiday"), true);
  EXPECT_EQ( root->Evaluate( Date ("2017-1-2"), "holiday"), true);
  EXPECT_EQ( root->Evaluate( Date ("2017-1-2"), "workday"), true);
  EXPECT_EQ( !root->Evaluate( Date ("2018-1-2"), "workday"), true);
}

TEST( ParseCondition, ComplexLogicalOperationNode2 )
{
  std::istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
  std::shared_ptr<Node> root = ParseCondition(is);
  EXPECT_EQ( root->Evaluate( Date ("2016-1-1"), "event"), true);
  EXPECT_EQ( root->Evaluate( Date ("2017-1-2"), "holiday"), true);
  EXPECT_EQ( root->Evaluate( Date ("2017-1-2"), "workday"), true);
  EXPECT_EQ( !root->Evaluate( Date ("2018-1-2"), "workday"), true);
}

TEST( ParseCondition, ComplexLogicalOperationNode3 )
{
  std::istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
  std::shared_ptr<Node> root = ParseCondition(is);
  EXPECT_EQ( root->Evaluate(Date ("2017-1-1"), "holiday"), true );
  EXPECT_EQ( !root->Evaluate(Date ("2017-1-2"), "holiday"), true );
}

TEST( ParseCondition, ComplexLogicalOperationNode4 )
{
  std::istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
  std::shared_ptr<Node> root = ParseCondition(is);
  EXPECT_EQ( root->Evaluate( Date ("1-1-1"), "2017-01-01"), true);
  EXPECT_EQ( !root->Evaluate( Date ("2016-1-1"), "event"), true);
  EXPECT_EQ( root->Evaluate(Date ("2016-1-2"), "event"), true);
}

TEST( ParseCondition, EmptyCondition )
{
  std::istringstream is("");
  std::shared_ptr<Node> root = ParseCondition(is);
  std::vector<std::string> vDates {"2016-12-31","20-6-30","2017-8-1"};
  for( auto& item : vDates )
    EXPECT_EQ( root->Evaluate( Date (item), ""), true);
}
