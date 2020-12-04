#include "main.h"

int main() 
{
	return 0;
}
/*
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if( range_end - range_begin < 2 )
		return;
	std::vector<typename RandomIt::value_type> vect;
	size_t rangeSize = std::distance(range_begin, range_end);
	vect.reserve( rangeSize );

	int coef = 3;
//	std::vector<RandomIt> vIt;
//	vIt.reserve(coef+1);
	
	auto itPrev = range_begin;
//	vIt.push_back(it);
	for(int i = 0; i != coef; ++i)
	{
		auto it = std::next(it, rangeSize/coef );
		MergeSort(itPrev
		vIt.push_back(it);
	}
//	auto range_one_third = std::next( range_begin , rangeSize / 3 );
//	auto range_two_third = std::next( range_one_third , rangeSize / 3 );
	for(int i = 0; i != coef; ++i)
		MergeSort( vIt[i], vIt[i+1]); 
	std::merge( vIt[0], vIt[1], vIt[1], vIt[2], std::back_inserter(vect) );
	std::merge( vect.begin(), vect.end(), vIt[2], vIt[3], std::back_inserter(vect) );
	std::move( std::begin(vect), std::end(vect), range_begin );
}*/
