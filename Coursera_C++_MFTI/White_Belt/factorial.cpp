#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>
int Factorial(int arg);

/*
void testFactorial()
{
	using TestData_t = std::vector<std::pair<int,int>>;
	const TestData_t vTest {{1,1},{-2,1},{4,24}};
	std::for_each(vTest.cbegin(),vTest.cend(),[](TestData_t::const_reference vTest)
		{
			assert(Factorial(vTest.first) == vTest.second);
		}
	);
}
*/

int Factorial(int arg)
{
	int result = 1;
	if(arg >= 1)
	{
		for(int i = arg; i != 0; --i)
			{
				result *= i;
			}
	}
		return result;
}

int main()
{
	int n {};
	std::cin >> n;
	std::cout << Factorial(n);
	return 0;
}
