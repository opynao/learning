#include "gtest/gtest.h"
#include "date.h"
#include "parse_date_event.h"

#include <sstream>
#include <ostream>
#include <string>

TEST ( ParseDate, CorrectDate )
{
	std::istringstream is("2017-11-24");
	Date date {ParseDate(is)};
	EXPECT_EQ( date.GetYear(), 2017 );
	EXPECT_EQ( date.GetMonth(), 11 );
	EXPECT_EQ( date.GetDay(), 24 );
}

TEST ( ParseDate, CorrectDate2 )
{
	std::istringstream is("0-2-30");
	Date date {ParseDate(is)};
	EXPECT_EQ( date.GetYear(), 0 );
	EXPECT_EQ( date.GetMonth(), 2 );
	EXPECT_EQ( date.GetDay(), 30 );
}

TEST ( Date, OstreamOperator )
{
	std::istringstream is("2017-11-24");
	Date date {ParseDate(is)};
	std::ostringstream oss;
	oss << date;
	std::string result {"2017-11-24"};
	EXPECT_EQ( oss.str(), result );
}
