#include "equation_stack.h"
#include <algorithm>
#include <iostream>

OperationPriority GetPriority(const Operation op)
{
	switch (op)
	{
		case Operation::MINUS:
		case Operation::PLUS:
			return OperationPriority::LOW;
		case Operation::DIV:
		case Operation::MULT:
			return OperationPriority::HIGH;
		default:
			return OperationPriority::HIGH;
	}
}

bool IsMore (const OperationPriority lhs, const OperationPriority rhs)
{
	if( lhs == OperationPriority::HIGH && rhs == OperationPriority::LOW )
		return true;
	return false;
}


Parser::Parser(std::istream& is)
{
	int number{};
	is >> number;
	stackOperations.push({ Operation::VOID, number });

	int numberOfOperations;
	is >> numberOfOperations;
	std::string operation;

	while (numberOfOperations--)
	{
		is >> operation;
		is >> number;
		auto it = m.find(operation);
		OperationPriority priorCurrent =  GetPriority( it->second );
		OperationPriority priorPrev = GetPriority( stackOperations.back().first );
		if( IsMore(priorCurrent, priorPrev) )
			bracketsCount++;
		stackOperations.push(std::make_pair(it->second, number));
	}
}

std::string ToString(Operation op)
{
	switch(op)
	{
		case Operation::MINUS:
			return "-";
		case Operation::PLUS:
			return "+";
		case Operation::MULT:
			return "*";
		case Operation::DIV:
			return "/";
		default:
			return "";

	}
}

void Parser::GetEquation(std::ostream& os)
{
	OperationPriority priorPrev = OperationPriority::LOW;
	while(bracketsCount--)
		os << "(";
	bool isFirst {true};
	while (!stackOperations.empty())
	{
		OperationPriority priorCurrent =  GetPriority( stackOperations.front().first );
		std::string strOp = ToString(stackOperations.front().first);
		if( IsMore( priorCurrent, priorPrev ) && !isFirst)
			os << ")";
		os << (strOp.empty() ? "": " " + strOp + " ") << stackOperations.front().second;
		isFirst = false;
		stackOperations.pop();
		priorPrev = priorCurrent;
	}
}
