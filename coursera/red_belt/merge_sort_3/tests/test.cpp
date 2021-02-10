#include "merge_sort.h"
#include "non_copy.h"

#include "gtest/gtest.h"

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
	std::vector< Noncopyable > v;
	v.reserve(3);
	v.push_back({2});
	v.push_back({1});
	v.push_back({5});
	LOGF;
	MergeSort( std::begin( v ), std::end( v ) );
	LOGF;
	std::vector< Noncopyable > result;
	result.reserve(3);
	result.push_back({1});
	result.push_back({2});
	result.push_back({5});
	EXPECT_EQ( v, result );	
}

TEST( MergeSort, AvoidCopying2 )
{
	std::vector< Noncopyable > v;
	v.reserve(9);
	v.push_back({6});
	v.push_back({4});
	v.push_back({7});
	v.push_back({6});
	v.push_back({4});
	v.push_back({4});
	v.push_back({0});
	v.push_back({1});
	v.push_back({5});

	LOGF;
	MergeSort( std::begin( v ), std::end( v ) );
	LOGF;
	std::vector< Noncopyable > r;
	r.reserve(9);
	r.push_back({0});
	r.push_back({1});
	r.push_back({4});
	r.push_back({4});
	r.push_back({4});
	r.push_back({5});
	r.push_back({6});
	r.push_back({6});
	r.push_back({7});

	EXPECT_EQ( v, r );
}
