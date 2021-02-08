#include "merge_sort.h"
#include "non_copy.h"

#include "gtest/gtest.h"

/*
TEST( MergeSort, For_Two_Elements_Range_Is_Sorted )
{
	std::vector<int> v = {6, 4};
	MergeSort(begin(v), end(v));
	const std::vector<int>  res {4, 6};
	EXPECT_EQ( res, v );
}

TEST( MergeSort, For_Eight_Elements_Range_Is_Sorted )
{
	std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
	MergeSort(begin(v), end(v));
	const std::vector<int>  res {0, 1, 4, 4, 4, 6, 6, 7};
	EXPECT_EQ( res, v );
}

*/
TEST( MergeSort, For_One_Element_Range_Not_Changed )
{
	std::vector<int> v = {6};
	MergeSort(begin(v), end(v));
	const std::vector<int>  res {6};
	EXPECT_EQ( res, v );
}

TEST( MergeSort, For_Empty_Range_Range_Not_Changed )
{
	std::vector<int> v = {};
	MergeSort(begin(v), end(v));
	const std::vector<int>  res {};
	EXPECT_EQ( res, v );
}

TEST( MergeSort, For_Four_Elements_Range_Is_Sorted )
{
	std::vector<int> v = {6, 4, 7, 6};
	MergeSort(begin(v), end(v));
	const std::vector<int>  res {4, 6, 6, 7};
	EXPECT_EQ( res, v );
}


TEST( MergeSort, For_Three_Elements_Range_Is_Sorted )
{
	std::vector<int> v = {2, 6, 4};
	MergeSort(begin(v), end(v));
	const std::vector<int>  res {2, 4, 6};
	EXPECT_EQ( res, v );
}

TEST( MergeSort, For_Nine_Elements_Range_Is_Sorted )
{
	std::vector<int> v = {6, 4, 2, 7, 6, 4, 4, 0, 1};
	MergeSort(begin(v), end(v));
	const std::vector<int>  res {0, 1, 2, 4, 4, 4, 6, 6, 7};
	EXPECT_EQ( res, v );
}

TEST( MergeSort, AvoidCopying )
{
	std::vector< Noncopyable > v (4);
	v.reserve(4);
	v.push_back({2});
	v.push_back({1});
	v.push_back({5});
	v.push_back({0});

	MergeSort( std::begin( v ), std::end( v ) );

	std::vector< Noncopyable > result;
	result.reserve(4);
	result.push_back({0});
	result.push_back({1});
	result.push_back({2});
	result.push_back({5});
	EXPECT_EQ( v, result );	
}
