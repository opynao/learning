#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

template <typename RandomIt> 
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
	auto itRangeBegin {std::lower_bound(range_begin, range_end, prefix, [] (const std::string& iter,const char prefix)->bool { return iter[0] == prefix; }) };
	if(itRangeBegin == range_end)	
	{
		itRangeBegin = std::lower_bound(range_begin, range_end, prefix, [] (const std::string& str, char prefix)->bool {return str[0] < prefix;});
		return {itRangeBegin, itRangeBegin};
	}
	auto itRangeEnd {std::lower_bound(itRangeBegin, range_end, prefix, [] (const std::string& iter, const char prefix)->bool { return iter[0] == prefix; }) };
	return {itRangeBegin, itRangeEnd};
}
