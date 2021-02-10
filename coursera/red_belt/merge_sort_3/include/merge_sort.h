#pragma once

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

#define LOGF std::cerr<< __FUNCTION__ << __LINE__ << std::endl

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) 
{
  // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
  int range_length = range_end - range_begin;
  if (range_length < 2)
    return;

  // 2. Создаем вектор, содержащий все элементы текущего диапазона
  std::vector<typename RandomIt::value_type> elements( std::make_move_iterator(range_begin), std::make_move_iterator(range_end));
  LOGF;
  // 3. Разбиваем вектор на три равные части
  auto one_third = elements.begin() + range_length / 3;
  auto two_third = elements.begin() + range_length * 2 / 3;
  LOGF;
  // 4. Вызываем функцию MergeSort от каждой трети вектора
  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());
  LOGF;
  // 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
  // back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
  std::vector<typename RandomIt::value_type> interim_result;
  interim_result.reserve( std::distance( elements.begin(), two_third ) );
  std::merge( std::make_move_iterator(elements.begin()), 
			  std::make_move_iterator(one_third), 
			  std::make_move_iterator(one_third), 
			  std::make_move_iterator(two_third),
			  std::back_inserter(interim_result));
  LOGF;
  // 6. С помощью алгоритма merge сливаем отсортированные части
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  std::merge( std::make_move_iterator(interim_result.begin()), 
		      std::make_move_iterator(interim_result.end()), 
			  std::make_move_iterator(two_third),
			  std::make_move_iterator(elements.end()),
			  range_begin);
}

/*
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
		vect.reserve( vect_.size() + std::distance( range_begin, range_end) );
		std::merge( std::make_move_iterator( std::begin(vect_) ), 
					std::make_move_iterator( std::end(vect_) ),
					std::make_move_iterator( range_begin ),
					std::make_move_iterator( range_end ),
					std::back_inserter(vect) );
		vect_ = std::move( vect );
	}

	std::vector<typename RandomIt::value_type>& GetMerged() 
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
		LOGF;
	}
	auto& vect = mg.GetMerged();
	LOGF;
	std::move( std::begin( vect ), std::end( vect ), range_begin );
}
*/
