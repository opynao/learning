#pragma once

#include <algorithm>
#include <vector>
#include <iterator>

template <typename RandomIt>
class Separator
{
public:
	Separator(RandomIt range_begin, RandomIt range_end, size_t num)
		: range_begin_ {range_begin}
		, range_end_ {range_end}
		, num_ {num}
		, chunkSize_ {std::distance(range_begin_, range_end_)/num_}
	{}
	
	RandomIt GetNextSplitPoint()
	{
		std::advance(range_begin_, chunkSize_);
		return range_begin_;
	}
	
	operator bool() const
	{
		return range_begin_ != range_end_;
	}

private:
	RandomIt range_begin_;
	RandomIt range_end_;
	size_t num_;
	size_t chunkSize_;
};

template <typename RandomIt>
class Merger
{
public:
	explicit Merger( size_t size )
	{
		vect_.reserve(size);
	}

	void Merge( RandomIt range_begin, RandomIt range_end )
	{
		if( vect_.empty())
		{
			std::move(range_begin, range_end, std::back_inserter(vect_));
			return;
		}
		std::vector<typename RandomIt::value_type> vect;
		vect.reserve(vect_.size());
		std::merge( std::make_move_iterator( std::begin(vect_) ), 
					std::make_move_iterator( std::end(vect_) ),
					std::make_move_iterator( range_begin ),
					std::make_move_iterator( range_end),
					std::back_inserter(vect) );
		std::swap(vect_, vect);
	}

	std::vector<typename RandomIt::value_type> GetMerged() const
	{
		return vect_;
	}
private:
	std::vector<typename RandomIt::value_type> vect_;
};


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	const size_t rangeSize = std::distance(range_begin, range_end);
	if( rangeSize < 2)
		return;
	
	Separator<RandomIt> sp (range_begin, range_end, 3);
	Merger<RandomIt> mg (rangeSize);
	auto previousSplitPoint = range_begin;

	while( sp )
	{
		auto nextSplitPoint = sp.GetNextSplitPoint();
		MergeSort( previousSplitPoint, nextSplitPoint );
		mg.Merge( previousSplitPoint, nextSplitPoint );
		previousSplitPoint = nextSplitPoint;
	}
	
	auto vect = mg.GetMerged();
	std::move( std::begin(vect), std::end(vect), range_begin );
}

