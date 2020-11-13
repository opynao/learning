#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <map>

template <typename T> T Sqr(T x);
template <typename T> std::vector<T> Sqr(std::vector<T> vector);
template <typename T1, typename T2> std::map<T1,T2> Sqr(std::map<T1,T2> m);
template <typename T1, typename T2> std::pair<T1,T2> Sqr(std::pair<T1,T2> p);



template <typename T>
T Sqr(T x)
{
	return x*x;
}

template <typename T>
std::vector<T> Sqr(std::vector<T> vector)
{
	for(T& item : vector)
	{
		item = Sqr(item);
	}
	return vector;
}	

template <typename T1, typename T2 >
std::map<T1,T2> Sqr(std::map<T1,T2> m)
{
	for(auto& item : m)
	{
		item.second = Sqr(item.second);
	}
	return m;
}

template <typename T1, typename T2>
std::pair<T1,T2> Sqr(std::pair<T1,T2> p)
{
	p.first = Sqr(p.first);
	p.second = Sqr(p.second);
	return p;
}


void testSqr_Int_3_ResultInt_9()
{
	int result = Sqr(3);
	assert(9 == result);
}

void testSqr_Double_3_5_ResultDouble_12_25()
{
	double result = Sqr(3.5);
	assert(12.25 == result);
}

void testSqr_Vector_Int_Result_AllSquareNumbers()
{
	std::vector<int> vInts {1,2,3,4};
	std::vector<int> result {1,4,9,16};
	assert(result == Sqr(vInts));
}


void testSqr_Map_Int_Result_All_Values_Are_Square()
{
	std::map<int,int> m 
	{
		{1,2},
		{2,3},
		{3,4}
	};
	std::map<int,int> result
	{
		{1,4},
		{2,9},
		{3,16}
	};
	assert(result == Sqr(m));
}

void testSqr_Pair_Result_Each_Elem_Sqr()
{
	std::pair<int,int> p {2,3};
	std::pair<int,int> result {4,9};
	assert(result == Sqr(p));
}

void testSqr_Vector_Map_Int()
{
	std::vector<std::map<int,int>> vMaps
	{
		{
			{1,2},
			{2,3},
			{3,4}
		}
	};
	std::vector<std::map<int,int>> result
	{
		{
			{1,4},
			{2,9},
			{3,16}
		}
	};
	assert(result == Sqr(vMaps));
}

/*
bool operator == (const std::vector<double>& rhs,const std::vector<double>& lhs)
{
	std::cout << __FUNCTION__ << std::endl;
	for(size_t i = 0; i != rhs.size(); ++i)
	{
		if(std::fabs(rhs[i] - lhs[i]) > std::numeric_limits<double>::epsilon())
			return false;
	}
	return true;
}

void testSqr_Vector_Double_Result_AllSquareNumbers()
{
	const std::vector<double> vDoubles {1.2,2.7,3.5};
	const std::vector<double> result {1.44,7.29,12.25};
	const std::vector<double> out = Sqr(vDoubles);
	bool b = result == out;
	assert(b);
}
*/

void RunAllTests()
{
	testSqr_Int_3_ResultInt_9();
	testSqr_Double_3_5_ResultDouble_12_25();
	testSqr_Vector_Int_Result_AllSquareNumbers();
//	testSqr_Vector_Double_Result_AllSquareNumbers();
	testSqr_Map_Int_Result_All_Values_Are_Square();
	testSqr_Pair_Result_Each_Elem_Sqr();
	testSqr_Vector_Map_Int();
}


int main()
{
	RunAllTests();
	return 0;
}
