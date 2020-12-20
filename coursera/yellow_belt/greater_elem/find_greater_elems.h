#pragma once
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border)
{
	std::vector<T> vResults;
	std::copy_if(std::cbegin(elements), std::cend(elements), std::back_inserter(vResults), [&border](const T& elem) { return elem > border; } );
	return vResults;
}


