#include <string>
#include <map>
#include <set>
#include <functional>
#include <cassert>
#include <utility>
#include <iostream>

using word_t = std::string;
using wordCount_t = size_t;
using synonymDictionary_t = std::map<word_t,std::set<word_t>>;
synonymDictionary_t synonymDict {};

void AddWordSynonym(const word_t first,const word_t second,synonymDictionary_t& synonymDict)
{
	auto itFind = synonymDict.find(first);
	if(synonymDict.cend() == itFind)
	{
		synonymDict.emplace(std::make_pair(first,std::set<word_t> {second}));
	}
	else
	{
		itFind->second.insert(second);
	}
}


void Add(const word_t first,const word_t second,synonymDictionary_t& synonymDict)
{
	AddWordSynonym(first,second,synonymDict);
	AddWordSynonym(second,first,synonymDict);
}


wordCount_t Count(const word_t word,synonymDictionary_t& synonymDict)
{
	auto itElement = synonymDict.find(word);
	return itElement->second.size();
}


bool Check(const word_t first, const word_t second, synonymDictionary_t& synonymDict)
{
	auto itElement = synonymDict.find(first);
	return itElement->second.count(second);
}


void ProcessAddCommand()
{
	word_t first;
	word_t second;
	std::cin >> first >> second;
	Add(first,second,synonymDict);
}


void ProcessCheckCommand()
{
	word_t first;
	word_t second;
	std::cin >> first >> second;
	std::cout << (Check(first,second,synonymDict) ? "YES" : "NO") << std::endl;
}


void ProcessCountCommand()
{
	word_t word;
	std::cin >> word;
	std::cout << Count(word,synonymDict) << std::endl;
}


void CallingModule()
{
	std::string command {};
	std::cin >> command;
	using TFoo = void (*)();
	std::map<std::string,TFoo> commands 
	{
		{"ADD",&ProcessAddCommand},
		{"CHECK",&ProcessCheckCommand},
		{"COUNT",&ProcessCountCommand}
	};
	auto itCall = commands.find(command);
	if(commands.cend() != itCall)
	{
		itCall->second();
	}
}

//-------------------------------------------------------------------

void testAddWordToTheDictionary_SynonymDictionaryChangeSize()
{
	synonymDictionary_t synonymDict {};
	Add("program","code",synonymDict);
	assert(2 == synonymDict.size());
}

void testAddWordToTheDictionary_SynonymDictionarySizeThreeWords()
{
	synonymDictionary_t synonymDict {};
	Add("program","code",synonymDict);
	Add("cipher","code",synonymDict);
	assert( 3 == synonymDict.size());
}

void testAddWordToTheDictionary_SynonymDictionaryContainKeys()
{
	synonymDictionary_t synonymDict {};
	Add("program","code",synonymDict);
	assert(synonymDict.cend() != synonymDict.find("program"));
}

void testCount_Synonyms()
{
	synonymDictionary_t synonymDict {};
	Add("program","code",synonymDict);
	Add("cipher","code",synonymDict);
	assert( 2 == Count("code",synonymDict));
}

void testCheck()
{
	synonymDictionary_t synonymDict {};
	Add("program","code",synonymDict);
	Add("cipher","code",synonymDict);
	assert( 1 == Check("code","program",synonymDict));
}


//--------------------------------------------------------------------


int main()
{
	int numberOfCalls {};
	std::cin >> numberOfCalls;
	while(numberOfCalls--)
	{
		CallingModule();
	}
	testAddWordToTheDictionary_SynonymDictionaryChangeSize();
	testAddWordToTheDictionary_SynonymDictionaryContainKeys();
	testAddWordToTheDictionary_SynonymDictionarySizeThreeWords();
	testCount_Synonyms();
	testCheck();
	return 0;
}
