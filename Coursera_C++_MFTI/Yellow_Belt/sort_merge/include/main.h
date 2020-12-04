#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <iostream>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if( range_end - range_begin < 2 )
		return;
	std::vector<typename RandomIt::value_type> vect;
	size_t rangeSize = std::distance(range_begin, range_end);
	vect.reserve( rangeSize );
	auto range_middle = std::next( range_begin , rangeSize / 2 );
	MergeSort( range_begin, range_middle ); 
	MergeSort( range_middle, range_end );
	std::merge( range_begin, range_middle, range_middle, range_end, std::back_inserter(vect) );
	std::move( std::begin(vect), std::end(vect), range_begin );
}
