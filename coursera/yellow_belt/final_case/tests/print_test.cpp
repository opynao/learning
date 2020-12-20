#include "database.h"
#include "date.h"
#include "parse_date_event.h"

#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <utility>
#include <sstream>


class PrintTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	Database db;
	std::ostringstream oss;
};


TEST_F( PrintTest, Dont_Repeating_Events_On_Different_Dates )
{
	std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","Holiday"},{"2017-03-08","Holiday"},{"2017-1-1","New Year"}};
	for(const auto& item : vInput)
	{
		std::istringstream issDate (item.first);
		std::istringstream issCase (item.second);
		const auto date = ParseDate(issDate);
		const auto event = ParseEvent(issCase);
		db.Add(date, event);
	}
	std::string resultOutput {"2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n"};
	db.Print(oss);
	EXPECT_EQ( oss.str(), resultOutput );
}

TEST_F( PrintTest, Repeating_Events_On_One_Date )
{
	std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","Holiday"},{"2017-03-08","Holiday"},{"2017-01-01","Holiday"},{"2017-1-1","New Year"}};
	for(const auto& item : vInput)
	{
		std::istringstream issDate (item.first);
		std::istringstream issCase (item.second);
		const auto date = ParseDate(issDate);
		const auto event = ParseEvent(issCase);
		db.Add(date, event);
	}
	std::string resultOutput {"2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n"};
	db.Print(oss);
	EXPECT_EQ( oss.str(), resultOutput );
}

TEST_F( PrintTest, In_One_Day_Some_Different_Cases )
{
	std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","Holiday"},{"2017-01-01","Holiday1"},{"2017-01-01","Holiday2"},{"2017-1-1","New Year"}};
	for(const auto& item : vInput)
	{
		std::istringstream issDate (item.first);
		std::istringstream issCase (item.second);
		const auto date = ParseDate(issDate);
		const auto event = ParseEvent(issCase);
		db.Add(date, event);
	}
	std::string resultOutput {"2017-01-01 Holiday\n2017-01-01 Holiday1\n2017-01-01 Holiday2\n2017-01-01 New Year\n"};
	db.Print(oss);
	EXPECT_EQ( oss.str(), resultOutput );
}

TEST ( Print, Print1 )
{
	Database db;
    db.Add({2019, 12, 1}, "a");
    db.Add({2019, 12, 1}, "b");
    db.Add({2019, 12, 2}, "c");
    db.Add({2019, 12, 2}, "d");
    db.Add({2019, 12, 3}, "e");
	std::ostringstream out;
    db.Print(out);
    EXPECT_EQ( "2019-12-01 a\n2019-12-01 b\n2019-12-02 c\n2019-12-02 d\n2019-12-03 e\n", out.str() );
}
