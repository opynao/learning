#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
//#include "tests.h"
//#include "print_vector_part.h"

//FOR ME

/*
void PrintVectorPart(const std::vector<int>& numbers, std::ostream& os)
{
	std::vector<int> copyVector {numbers};
	auto result = std::find_if(std::cbegin(copyVector), std::cend(copyVector), [] (decltype(copyVector)::const_reference num) { return num < 0; });
	copyVector.erase(result, std::end(copyVector));
	std::reverse(std::begin(copyVector), std::end(copyVector));
	for(const auto& item : copyVector)
	{
		os << item;
		if(item != *copyVector.rbegin())
			os << " ";
	}
}
*/

//FOR COURSERA

void PrintVectorPart(const std::vector<int>& numbers)
{
	std::vector<int> copyVector {numbers};
	auto result = std::find_if(std::cbegin(copyVector), std::cend(copyVector), [] (decltype(copyVector)::const_reference num) { return num < 0; });
	copyVector.erase(result, std::end(copyVector));
	std::reverse(std::begin(copyVector), std::end(copyVector));
	for(const auto& item : copyVector)
	{
		std::cout << item;
//		if(item != *copyVector.rbegin())
			std::cout << " ";
	}
}

int main()
{
//	TestAll();
	return 0;
}
