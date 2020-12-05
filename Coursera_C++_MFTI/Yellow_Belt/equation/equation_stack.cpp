#include <iostream>
#include <string>
#include <queue>

class Parser
{
public:
	explicit Parser(std::istream&);
	void GetEquation(std::ostream&);
private:
	std::string firstNumber;
	std::string operation {};
	std::queue<std::string> dequeOperations {};
	void GetBrackets(std::string& result) const;
};

Parser::Parser(std::istream& is)
{
	std::string line;
	is >> firstNumber;		

	int numberOfOperations;
	is >> numberOfOperations;
	int a = 2*numberOfOperations;
	while(a--)
	{
		is >> operation;
		dequeOperations.push(operation);
	}
}

void Parser::GetEquation(std::ostream& os)
{
	if(dequeOperations.empty())
	{			
		os << firstNumber; 
		return;
	}
	std::string result = firstNumber;
	int count = dequeOperations.size();
	for(int i = 0; i != count/2 - 1; i++)
		os << "(";
	os << "(" << firstNumber << ")";
	while(count)	
	{
		os << " " << dequeOperations.front();
		dequeOperations.pop();
		os << " " << dequeOperations.front(); 
		if(count != 2)
			std::cout << ")";
		dequeOperations.pop();
		count -= 2;
	}
}

int main()
{
	Parser pr(std::cin);
	pr.GetEquation(std::cout);
	return 0;
}

