#include <cassert>
#include <vector>
#include <algorithm>

template <typename T>
T Sqr(T x)
{
	return x*x;
}

template <typename T>
std::vector<T> Sqr(const std::vector<T>& vector)
{
	std::vector<T> result;
	std::transform(vector.cbegin(),vector.cend(),std::back_inserter(result),Sqr<T>);
	return result;
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
/*
void testSqr_Vector_Double_Result_AllSquareNumbers()
{
	std::vector<int> vInts {1.2,2.7,3.5};
	std::vector<int> result {1.44,4,9,16};
	
	assert(result == Sqr(vInts));
}
*/

void RunAllTests()
{
	testSqr_Int_3_ResultInt_9();
	testSqr_Double_3_5_ResultDouble_12_25();
	testSqr_Vector_Int_Result_AllSquareNumbers();
}



int main()
{
	RunAllTests();
	return 0;
}
