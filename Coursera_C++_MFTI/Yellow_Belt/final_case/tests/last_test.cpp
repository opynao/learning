#include "database.h"
#include "date.h"
#include "parse_date_event.h"

#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <utility>
#include <sstream>


class LastTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		for(const auto& item : vInput)
		{
			std::istringstream issCase (item.second);
			const auto event = ParseEvent(issCase);
			db.Add(Date (item.first), event);
		}
	}
	
	Database db;
	
	std::vector<std::pair<std::string,std::string>> vInput
	{
		{"2017-01-01","New Year"},
		{"2017-03-08","Holiday1"},
		{"2017-01-03","even1"},
		{"2017-01-03","event2"},
		{"2017-01-01","Holiday"},
		{"2017-01-02","event1"},
		{"2017-01-03","event3"},
		{"2017-01-02","event3"}
	};
};


TEST_F( LastTest, Test_Last_Throws_Exception )
{
	bool isException {false};
	try
	{
		auto date_event = db.Last(Date ("2016-12-21"));
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}


TEST_F( LastTest, Test_Last_Output_Last_Case_In_One_Day )
{
	auto date_event = db.Last(Date ("2017-01-01"));
	std::pair< Date, Event_t > result = { Date ("2017-01-01"),"Holiday"};
	EXPECT_EQ( date_event, result );
}


TEST_F( LastTest, Test_Last_Output_Last_Case )
{
	auto date_event = db.Last(Date ("2017-06-06"));
	std::pair< Date, Event_t > result = { Date ("2017-03-08"),"Holiday1" };
	EXPECT_EQ( date_event, result );
}

TEST_F( LastTest, Find_Largest_Among_All_Dates_and_Last_Added_Event_At_That_Date )
{
	const auto date_event = db.Last(Date ("2017-03-07"));
	const std::pair< Date, Event_t > result = { Date ("2017-01-03"),"event3" };
	EXPECT_EQ( date_event, result );
}
