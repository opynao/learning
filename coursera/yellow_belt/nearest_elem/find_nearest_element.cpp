#include <set>
#include <iterator>
#include <iostream>
#include "find_nearest_element.h"

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border)
{
	if(numbers.empty())
		return std::cend(numbers);

	auto itElem = numbers.lower_bound(border);
	auto itPrev = std::prev(itElem);

	if (itElem == numbers.cbegin())
		return itElem;
	if (itElem == numbers.cend())
		return std::prev(itElem);

	if(std::abs(border - *itElem) >= std::abs(border - *itPrev))
		return itPrev;

	return itElem;
}
