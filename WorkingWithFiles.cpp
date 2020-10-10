#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>


void ReadFromStreamToOutput(std::istream& is,std::ostream& os)
{
	std::vector<std::string> vStrings;
	std::string str ;
	while(std::getline(is,str))
	{
		vStrings.emplace_back(str + '\n');
	}
	for(const auto& item : vStrings)
	{
		os << item;
	}

}

void test()
{
	std::string str;
	std::ifstream ifs ("input.txt",std::ios::binary);
	std::copy(std::istream_iterator<char>(ifs),std::istream_iterator<char>(),std::back_inserter(str));	
	std::stringstream iss;
       	iss.str(str);
	std::stringstream oss;
	ReadFromStreamToOutput(iss,oss);
	std::cerr << iss.str().size() << " " << oss.str().size() << std::endl << " " << str.size();	
	assert(oss.str().size() == iss.str().size());
	assert(oss.str() == iss.str());
}

int main()
{
	std::ifstream ifs ("input.txt");
	ReadFromStreamToOutput(ifs,std::cout);
	test();
	return 0;
}
