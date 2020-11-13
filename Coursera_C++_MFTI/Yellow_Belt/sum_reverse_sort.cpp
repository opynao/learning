#include <vector>
#include <string>
#include <algorithm>
#include "sum_reverse_sort.h"

int Sum(int x, int y)
{
	return x+y;
}

void Sort(std::vector<int>& nums)
{
	std::sort(nums.begin(), nums.end());
}

std::string Reverse(std::string s)
{
	std::string result;
	copy(s.rbegin(),s.rend(),std::back_inserter(result));
	return result;
}
/*
int main()
{
	return 0;
}*/
