#include "parse_date.h"

#include <stdexcept>

Date ParseDate(std::istream& is)
{
	std::string strDate;
	Date date;
	is >> strDate;
	std::string result;
	if(!Date::CheckFormat(strDate))
	{
		result = "Wrong date format" + strDate + "\n";
		throw std::out_of_range(result);
	}

	date = Date(strDate);
	
	if(date.GetMonth() < 1 || date.GetMonth() > 12)
	{
		result = "Month value is invalid";
		throw std::out_of_range(result);
	}	
	if(date.GetDay() < 1 || date.GetDay() > 31)
	{
		result = "Day value is invalid";
		throw std::out_of_range(result);
	}
	return date;
}

// Alternative version 
// (if function doesn't throw errors and ParseDate returns bool)
/*	if(!Date::CheckFormat(strDate))
	{
		std::cout << "Wrong date format: " << strDate << std::endl;
		return;
	}

	date = Date(strDate);
	
	if(date.GetMonth() < 1 || date.GetMonth() > 12)
	{
		std::cout << "Month value is invalid: " << date.GetMonth() << std::endl;
		return;
	}
		
	if(date.GetDay() < 1 || date.GetDay() > 31)
	{
		std::cout << "Day value is invalid: " << date.GetDay() << std::endl;
		return;
	}
	return date;
}*/



