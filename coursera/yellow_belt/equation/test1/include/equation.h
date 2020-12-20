#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <algorithm>

enum class Operation
{
	VOID,
	PLUS,
	MINUS,
	MULT,
	DIV
};

std::map< std::string, Operation > m
{
	{ "-", Operation::MINUS },
	{ "+", Operation::PLUS },
	{ "/", Operation::DIV },
	{ "*", Operation::MULT }
};

enum class OperationPriority
{
	HIGH,
	LOW
};

class Parser
{
public:
	explicit Parser(std::istream&);
	void GetEquation(std::ostream&);
private:
	std::stack<std::pair<Operation, int>> stackOperations{};
};


