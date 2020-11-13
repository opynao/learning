#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <iterator>

using vInput_t = std::vector<int>;


void ReadFromInput(std::ifstream& ifs,vInput_t& vInput, size_t& numberOfColumns)
{
	size_t numberOfRows {};
	ifs >> numberOfRows >> numberOfColumns;
	std::string row {}, word {};
	
	while(std::getline(ifs,row))
	{
		std::stringstream ss(row);
		while(std::getline(ss,word,','))
		{
			int number {std::stoi(word)};
			vInput.push_back(number);	
		}
	}
}


void PrintTable(std::ostream& os, const vInput_t& vInput, const size_t numberOfColumns)
{
	for(size_t i = 0; i != vInput.size(); ++i)
	{
		const bool isEndOfCol = (i % numberOfColumns);
		const bool isNewLine = (i != 0) && !isEndOfCol && (i < vInput.size());
		if(isNewLine)
			os << std::endl;
		if(isEndOfCol)
			os << ' ';	
		os << std::setw(10) << std::right << vInput[i];
	}
}


int main()
{
	std::ifstream ifs("input.txt");
	size_t numberOfColumns {};
	vInput_t vInput {};
        ReadFromInput(ifs, vInput, numberOfColumns);
	PrintTable(std::cout, vInput, numberOfColumns);
	return 0;
}
