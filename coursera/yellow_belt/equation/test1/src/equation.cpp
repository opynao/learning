#include "equation.h"

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <algorithm>



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
		stackOperations.push(std::make_pair(it->second, number));
	}
}

void Parser::GetEquation(std::ostream& os)
{
	std::string result;
	OperationPriority priorPrev = OperationPriority::LOW;
	OperationPriority priorNext = OperationPriority::LOW;
	int bracketsCount = 0;
	while (stackOperations.top().first != Operation::VOID)
	{

		switch (stackOperations.top().first)
		{
		case Operation::MINUS:
			priorNext = OperationPriority::LOW;
			break;
		case Operation::PLUS:
			priorNext = OperationPriority::LOW;
			break;
		case Operation::DIV:
			priorNext = OperationPriority::HIGH;
			break;
		case Operation::MULT:
			priorNext = OperationPriority::HIGH;
			break;
		case Operation::VOID:
			priorNext = OperationPriority::LOW;
			break;
		}
		if (priorNext == OperationPriority::LOW && priorPrev == OperationPriority::HIGH)
		{
			result += ")";
			bracketsCount++;
		}
		auto it = std::find_if(m.begin(), m.end(),
			[this](std::pair<std::string, Operation> pr)
			{
				return pr.second == stackOperations.top().first;

			});

		result += std::to_string(stackOperations.top().second) + " " + it->first + " ";
		stackOperations.pop();
		priorPrev = priorNext;
	}
	result += std::to_string(stackOperations.top().second);
	std::reverse(result.begin(), result.end());
	result.insert(0, bracketsCount, '(');
	os << result;

}


