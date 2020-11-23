//#include "equation.h"
#include <iostream>
#include <string>
#include <vector>

class Parser
{
public:
	explicit Parser(std::istream&);
	void GetEquation(std::ostream&) const;
private:
	std::string firstNumber;
	std::string operation {};
	std::string number {};
	std::vector<std::pair<std::string,std::string>> dequeOperations {};
	void GetBrackets(std::string& result) const;
};

Parser::Parser(std::istream& is)
{
	std::string line;
	is >> firstNumber;		

	int numberOfOperations;
	is >> numberOfOperations;
	dequeOperations.reserve(numberOfOperations);

	while(numberOfOperations--)
	{
		is >> operation;		
		is >> number;	
		dequeOperations.push_back(std::make_pair(operation,number));
	}
}

void Parser::GetEquation(std::ostream& os) const
{
	if(dequeOperations.empty())
	{			
		os << firstNumber; 
		return;
	}
	std::string result = firstNumber;
	for(size_t i = 0; i != dequeOperations.size(); i++)
	{
		GetBrackets(result);
		result += " " + dequeOperations[i].first + " " + dequeOperations[i].second; 
	}
	os << result;
}

void Parser::GetBrackets(std::string& result) const
{
	result = "(" + result + ")";
}

int main()
{
	Parser pr(std::cin);
	pr.GetEquation(std::cout);
	return 0;
}

