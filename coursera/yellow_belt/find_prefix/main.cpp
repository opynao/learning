#include "find_started_from_char.h"
/*#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <tuple>

template <typename RandomIt> 
std::pair<RandomIt, RandomIt> FindStartsWithChar(RandomIt range_begin, RandomIt range_end, char prefix, size_t pos)
{
	const auto itLB = std::lower_bound(range_begin, range_end, prefix, 
			[&pos] ( const std::string& str, const char prefix) 
			{ 
				return str.size() < (pos + 1) ? true : str[pos] < prefix;
			});
	const auto itUB = std::upper_bound( itLB, range_end, prefix, 
			[&pos] ( const char prefix, const std::string& str ) 
			{ 
				return str.size() < (pos + 1) ? true : prefix < str[pos];
			});

	return { itLB, itUB };
}


template <typename RandomIt> 
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const std::string& prefix)
{
	RandomIt itLB = range_begin;
	RandomIt itUB = range_end;

	for( size_t i = 0; itLB != itUB && i != prefix.size(); ++i) 
		std::tie(itLB, itUB) = FindStartsWithChar( itLB, itUB, prefix[i], i);
	return { itLB, itUB };
}
*/
int main()
{
	return 0;
}
