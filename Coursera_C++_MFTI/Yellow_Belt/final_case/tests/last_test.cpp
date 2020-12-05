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
	}
	Database db;
};


TEST_F( LastTest, Test_Last_Throws_Exception )
{
	std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","New Year"},{"2017-03-08","Holiday"},{"2017-01-01","Holiday"}};
	for(const auto& item : vInput)
	{
		std::istringstream issDate (item.first);
		std::istringstream issCase (item.second);
		const auto date = ParseDate(issDate);
		const auto event = ParseEvent(issCase);
		db.Add(date, event);
	}
	bool isException {false};
	try
	{
		std::istringstream iss ("2016-12-31");
		std::string event = db.Last(ParseDate(iss));
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST_F( LastTest, Test_Last_Output_Last_Case_In_One_Day )
{
	std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","New Year"},{"2017-03-08","Holiday1"},{"2017-01-01","Holiday"}};
	for(const auto& item : vInput)
	{
		std::istringstream issDate (item.first);
		std::istringstream issCase (item.second);
		const auto date = ParseDate(issDate);
		const auto event = ParseEvent(issCase);
		db.Add(date, event);
	}
	std::istringstream iss ("2017-01-01");
	std::string event = db.Last(ParseDate(iss));
	std::string result = "Holiday";
	EXPECT_EQ( event, result );
}

TEST_F( LastTest, Test_Last_Output_Last_Case )
{
	std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","New Year"},{"2017-03-08","Holiday1"},{"2017-01-01","Holiday"}};
	for(const auto& item : vInput)
	{
		std::istringstream issDate (item.first);
		std::istringstream issCase (item.second);
		const auto date = ParseDate(issDate);
		const auto event = ParseEvent(issCase);
		db.Add(date, event);
	}
	std::istringstream iss ("2017-06-06");
	std::string event = db.Last(ParseDate(iss));
	std::string result = "Holiday1";
	EXPECT_EQ( event, result );
}
