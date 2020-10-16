#include <utility>
#include <string>
#include <cassert>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using pairStrings_t = std::pair<std::string,std::string>;
using wordsCount_t = size_t;
using mapChars_t = std::map<char,wordsCount_t>;

mapChars_t MakeMapFromString(const std::string& str)
{
	mapChars_t m {};
	std::for_each(std::cbegin(str),std::cend(str),
			[&m](std::string::const_reference ch)
			{
				++m[ch];
			}
	);
	return m;
}

bool IsAnagram(const pairStrings_t& pairStr)
{
	return MakeMapFromString(pairStr.first) == MakeMapFromString(pairStr.second);
}

void test_IsAnagram_WordsAreAnagrams()
{
	assert(true == IsAnagram({"tea","eat"}));
}

void test_IsAnagram_WordsNotAnagrams()
{
	assert(false == IsAnagram({"find","search"}));
}

int main()
{
	size_t numberOfPairs {};
	std::cin >> numberOfPairs;
	std::vector<pairStrings_t> vPairStrings {};
	vPairStrings.reserve(numberOfPairs);
	while(numberOfPairs--)
	{
		pairStrings_t words;
		std::cin >> words.first >> words.second;
		vPairStrings.emplace_back(words.first,words.second);
	}
	std::for_each(std::cbegin(vPairStrings),std::cend(vPairStrings),
			[](decltype(vPairStrings)::const_reference pr){std::cout << (IsAnagram(pr)? "YES" : "NO") << std::endl;});
	test_IsAnagram_WordsAreAnagrams();
	test_IsAnagram_WordsNotAnagrams();
	return 0;
}
