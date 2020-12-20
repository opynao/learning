#include "date.h"
#include <sstream>
#include <ostream>
#include <iomanip>

Date::Date(const std::string& strDate)
{
	std::istringstream is (strDate);
	is >> year;
	is.get();
	is >> month;
	is.get();
	is >> day;
}

Date::Date(const int y, const int m, const int d)
	: year {y}
	, month {m}
	, day {d}
{
}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

bool operator<(const Date& lhs, const Date& rhs)
{
	std::vector<int> vLhs { lhs.GetYear(), lhs.GetMonth(), lhs.GetDay() };
	std::vector<int> vRhs { rhs.GetYear(), rhs.GetMonth(), rhs.GetDay() };
	if ( vLhs < vRhs)
		return true;
	return false;
}

bool operator==(const Date& lhs, const Date& rhs)
{
	if(lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay())
		return true;
	return false;
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs ==rhs);
}

bool operator>(const Date& lhs, const Date& rhs)
{
	return rhs < lhs;
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return !(rhs < lhs);
}


std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << std::setw(4) << std::setfill('0') << date.GetYear() << '-' << std::setw(2) << date.GetMonth() << '-' << std::setw(2) << date.GetDay();
	return os;
}
