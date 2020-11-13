#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>

int main()
{
	size_t n {};
	std::cin >> n;
	std::vector<std::string> vStrings {};
	vStrings.reserve(n);
	std::copy(std::istream_iterator<std::string>(std::cin),std::istream_iterator<std::string>(),std::back_inserter(vStrings));
	auto toLower = [](std::string str)->std::string
	{
		std::for_each(std::begin(str),std::end(str),[] (char& ch)
		{
			ch = std::tolower(ch);
		}
		);
	       return str;
	};
	std::for_each(std::begin(vStrings),std::end(vStrings),toLower);
	std::sort(std::begin(vStrings),std::end(vStrings),[&toLower](const std::string& first, const std::string& second)->bool
       	{
		return toLower(first) < toLower(second);
	}
	);
	std::copy(std::cbegin(vStrings),std::cend(vStrings),std::ostream_iterator<std::string>(std::cout," "));
	return 0;
}
