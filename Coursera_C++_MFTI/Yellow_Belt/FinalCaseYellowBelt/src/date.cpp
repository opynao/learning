#include "date.h"

bool operator<(const Date& lhs, const Date& rhs)
{

	if(lhs.GetYear() < rhs.GetYear())
		return true;
	
	if(lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth())
		return true;
	
	if(lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay())
		return true;
	return false;
}

Date::Date(const std::string& strDate)
{
	std::istringstream is (strDate);
	is >> year;
	is.get();
	is >> month;
	is.get();
	is >> day;
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

bool Date::CheckFormat(const std::string& date)
{
	if(date.empty())
		return false;
	size_t i = 0;

	for( size_t j : {1,2,3} )
	{
		if(date[i] == '-' || date[i] == '+')
	        	++i;
		
		if (!std::isdigit(date[i]))
			return false;
	
		while(std::isdigit(date[i]) && i < date.size() - 1)
			++i;

		if( j == 3 && !std::isdigit(date[i]))
			return false;
		
		if (j != 3)
		{
			if( date[i++] != '-')
				return false;
		}
	}

	if( i == date.size() - 1)
		return true;
	
	return false;
}
