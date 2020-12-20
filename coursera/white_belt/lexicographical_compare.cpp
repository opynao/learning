#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <set>



int main()
{
	std::set<std::string> sStrings;
	std::copy(std::istream_iterator<std::string>(std::cin),std::istream_iterator<std::string>(),std::inserter(sStrings,sStrings.end()));
	std::cout << *sStrings.begin();
	return 0;
}
