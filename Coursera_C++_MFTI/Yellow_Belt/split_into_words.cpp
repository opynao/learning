#include <sstream>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> SplitIntoWords(const std::string& s)
{
	std::stringstream ss;
	std::string str;
	std::vector<std::string> vResults;
	ss.str(s);
	while(!ss.eof())
	{
		std::getline(ss, str, ' ');
		vResults.push_back(str);
	}
	return vResults;
}

int main() 
{
/*	std::string s = "C Cpp Java Python";

	std::vector<std::string> words = SplitIntoWords(s);
	std::cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) 
	{
		if (it != begin(words)) 
		{
			std::cout << "/";
		}
		std::cout << *it;
	}
	std::cout << std::endl;
*/	return 0;
}
