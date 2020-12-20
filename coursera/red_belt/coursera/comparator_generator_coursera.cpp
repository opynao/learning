#include "airline_ticket.h"
#include <string>
#include <vector>

#define SORT_BY(field) ([](const AirlineTicket& lhs, const AirlineTicket& rhs) {return lhs.field < rhs.field;}) 

bool operator<(const Date& lhs, const Date& rhs)
{
	const std::vector<int> vLhs { lhs.year, lhs.month, lhs.day };
	const std::vector<int> vRhs { rhs.year, rhs.month, rhs.day };
	return vLhs < vRhs;
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day);
}

bool operator<(const Time& lhs, const Time& rhs)
{
	const std::vector<int> vLhs { lhs.hours, lhs.minutes };
	const std::vector<int> vRhs { rhs.hours, rhs.minutes };
	return vLhs < vRhs;
}


int main() 
{
}


