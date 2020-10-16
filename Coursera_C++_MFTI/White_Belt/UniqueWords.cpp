#include <set>
#include <string>
#include <iostream>

int main()
{
	size_t numberOfCalls {};
	std::cin >> numberOfCalls;
	std::set<std::string> setOfWords {};
	while(numberOfCalls--)
	{
		std::string word {};
		std::cin >> word;
		setOfWords.insert(word);
	}
	std::cout << setOfWords.size();
	return 0;
}
