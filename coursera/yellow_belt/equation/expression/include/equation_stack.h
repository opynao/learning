#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <map>

enum class Operation
{
	VOID,
	PLUS,
	MINUS,
	MULT,
	DIV
};

static const std::map< std::string, Operation > m
{
	{ "-", Operation::MINUS },
	{ "+", Operation::PLUS },
	{ "/", Operation::DIV },
	{ "*", Operation::MULT },
	{ "", Operation::VOID }
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
	std::queue<std::pair<Operation, int>> stackOperations{};
	int bracketsCount {0};
};
