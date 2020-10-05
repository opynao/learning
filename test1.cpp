#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
std::vector<int> SymbolCountInEachString(const std::vector<std::string>&);

void testSymbolCountInEachString_ForEmptyVectorStrings_EmptyVectorSymbolCount()
{
	std::vector<std::string> vStrings {};
	std::vector<int> vSymbolCounts = SymbolCountInEachString(vStrings);
	assert(vSymbolCounts.empty());	
}

void testSymbolCountInEachString_ForVectorEmptyStrings_VectorSameSizeWithZeroStringLengths()
{
	std::vector<std::string> vStrings {{},{},{}};
	std::vector<int> vSymbolCounts = SymbolCountInEachString(vStrings);
	assert(vSymbolCounts == std::vector<int>(3,0));
}

void testSymbolCountInEachString_ForVectorNotEmptyStrings_VectorSameSizeWithStringsLengths()
{
	std::vector<std::string> vStrings {"there", "there are three pigs", "red hat"};
	std::vector<int> vSymbolCounts {5,20,7};
	assert(vSymbolCounts == SymbolCountInEachString(vStrings));
}

std::vector<int> SymbolCountInEachString(const std::vector<std::string>& vStrings)
{
	std::vector<int> vSymbolCounts;
	auto PushStringSize = [](std::vector<int>& vSymbolCounts)
	{ 
		return [&vSymbolCounts](const std::string& str)
		{
			vSymbolCounts.push_back(str.size());
		};
	};
	std::for_each(vStrings.cbegin(),vStrings.cend(),PushStringSize(vSymbolCounts));
	return vSymbolCounts;
}

void RunAllTests()
{
	testSymbolCountInEachString_ForEmptyVectorStrings_EmptyVectorSymbolCount();
	testSymbolCountInEachString_ForVectorEmptyStrings_VectorSameSizeWithZeroStringLengths();
	testSymbolCountInEachString_ForVectorNotEmptyStrings_VectorSameSizeWithStringsLengths();
}


int main()
{
	RunAllTests();	
	return 0;
}
