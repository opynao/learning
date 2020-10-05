#include <iostream>
#include <string>
long int FindSecondOccurence(const std::string&,const char);
/*
void TestFindSecondOccurence()
{
	using TestData_t = std::vector<std::pair<std::string,int>>; 
	const char ch {'f'};
	const TestData_t vStrings {{"comfort",-1},{"coffee",3},{"car",-2}};
	std::for_each(vStrings.cbegin(),vStrings.cend(),
			[](TestData_t::const_reference& testData)
		       	{
				assert(FindSecondOccurence(testData.first,ch) == testData.second);
			}
	);
}

*/
long int FindSecondOccurence(const std::string& str, const char ch)
{
	size_t index = str.find(ch);
	if (index == std::string::npos)
		return -2;
	index = str.find(ch,index+1);	
	if (index == std::string::npos)
		return -1;
	return index;
}

int main()
{
	std::string str;
	std::cin >> str;
	std::cout << FindSecondOccurence(str,'f');
	return 0;
}
