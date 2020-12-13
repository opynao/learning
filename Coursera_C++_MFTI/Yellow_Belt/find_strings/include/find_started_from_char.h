#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

template <typename RandomIt> 
std::pair<RandomIt, RandomIt> FindStartsWithChar(RandomIt range_begin, RandomIt range_end, char prefix)
{
	const auto itLB = std::lower_bound(range_begin, range_end, prefix, 
			[] ( const std::string& str, const char prefix) 
			{ 
				return str.empty() ? true : str[0] < prefix;
			});
	const auto itUB = std::upper_bound( itLB, range_end, prefix, 
			[] ( const char prefix, const std::string& str ) 
			{ 
				return str.empty() ? true : prefix < str[0];
			});

	return { itLB, itUB };
}
