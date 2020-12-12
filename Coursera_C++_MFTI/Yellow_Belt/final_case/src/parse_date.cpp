#include "parse_date_event.h"

#include <stdexcept>

Date ParseDate(std::istream& is)
{
	std::string strDate;
	Date date;
	is >> strDate;
	std::string result;
	date = Date(strDate);
	return date;
}



