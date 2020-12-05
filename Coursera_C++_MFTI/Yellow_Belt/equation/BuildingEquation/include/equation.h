#pragma once
#include <iostream>
#include <string>
#include <vector>

class Parser
{
public:
	explicit Parser(std::istream&);
	void GetEquation(std::ostream&) const;
private:
	int firstNumber;
	std::string operation {};
	int number {};
	std::vector<std::string> dequeOperations {};
	std::vector<int> dequeNumbers {};
	void GetBrackets(std::string& result) const;
};

