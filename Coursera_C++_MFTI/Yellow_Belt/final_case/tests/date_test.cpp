#include "date.h"
#include "parse_date_event.h"
#include "gtest/gtest.h"



TEST ( ParseDate, CorrectDate )
{
	std::istringstream is("2020-11-27");
	Date date {ParseDate(is)};
	EXPECT_EQ( date.GetYear(), 2020 );
	EXPECT_EQ( date.GetMonth(), 11 );
	EXPECT_EQ( date.GetDay(), 27 );
}

TEST ( ParseDate, CorrectDate2 )
{
	std::istringstream is("0-2-30");
	Date date {ParseDate(is)};
	EXPECT_EQ( date.GetYear(), 0 );
	EXPECT_EQ( date.GetMonth(), 2 );
	EXPECT_EQ( date.GetDay(), 30 );
}

TEST ( CheckFormat, CorrectnessOfDate) 
{
	EXPECT_EQ( true, Date::CheckFormat("1-1-1"));
    EXPECT_EQ( true, Date::CheckFormat("-1-1-1"));
	EXPECT_EQ( true, Date::CheckFormat("1--1-1"));
	EXPECT_EQ( false, Date::CheckFormat("1---1-1"));
	EXPECT_EQ( true, Date::CheckFormat("1-+1-+1"));
	EXPECT_EQ( true, Date::CheckFormat("-1-1-1"));
	EXPECT_EQ( false, Date::CheckFormat("--1-1-1"));
	EXPECT_EQ( false, Date::CheckFormat("-1-1"));
	EXPECT_EQ( false, Date::CheckFormat("1-1-"));
	EXPECT_EQ( false, Date::CheckFormat("&1-1-1"));
	EXPECT_EQ( false, Date::CheckFormat("1-1-1-"));
}

TEST ( ParseDate, ExceptionWrongDateFormat ) 
{
	std::istringstream is("1---1-1");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST ( ParseDate, ExceptionWrongDateFormat2 ) 
{
	std::istringstream is("--1-1-1");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST ( ParseDate, ExceptionWrongDateFormat3 ) 
{
	std::istringstream is("-1-1");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST ( ParseDate, ExceptionWrongDateFormat4 ) 
{
	std::istringstream is("1-1-");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST ( ParseDate, ExceptionWrongDateFormat5 ) 
{
	std::istringstream is("&1-1-1");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST ( ParseDate, ExceptionWrongDateFormat6 ) 
{
	std::istringstream is("1-1-1-");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST ( ParseDate, ExceptionWrongMonth ) 
{
	std::istringstream is("2020-0-15");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}

TEST ( ParseDate, ExceptionWrongDay ) 
{
	std::istringstream is("2020-1-35");
	bool isException {false};
	try
	{
		Date date {ParseDate(is)};
	}
	catch(...)
	{
		isException = true;
	}
	EXPECT_EQ( isException, true );
}
