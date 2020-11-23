#include "parse_date.h"

Date ParseDate(const std::istream& is)
{
	if(!Date::CheckFormat(strDateFormat))
	{
		std::cout << "Wrong date format: " << strDateFormat << std::endl;
		return false;
	}

	date = Date(strDateFormat);
	
	if(date.GetMonth() < 1 || date.GetMonth() > 12)
	{
		std::cout << "Month value is invalid: " << date.GetMonth() << std::endl;
		return false;
	}
		
	if(date.GetDay() < 1 || date.GetDay() > 31)
	{
		std::cout << "Day value is invalid: " << date.GetDay() << std::endl;
		return false;
	}

	return true;
}

