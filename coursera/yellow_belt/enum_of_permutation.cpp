#include <vector>
#include <iostream>
#include <algorithm>


void PrintVector(std::vector<std::vector<int>>& v)
{
	for(const auto& item : v)
	{
		for(const auto& i : item)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}

void PrintPermutation(const int num)
{
	std::vector<int> vPermutation;
	for( int i = 1; i <= num; i ++)
	{
		vPermutation.push_back(i);
	}
	std::vector<std::vector<int>> vResults;
	do
	{	
		vResults.push_back(vPermutation);
	}
	while(std::next_permutation(vPermutation.begin(), vPermutation.end()));
	std::sort(vResults.rbegin(), vResults.rend());
	PrintVector(vResults);
}

int main()
{
	int num;
	std::cin >> num;
	PrintPermutation(num);
	return 0;
}
