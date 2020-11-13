#include <memory>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
//---------------------------------------------------------

using operation_t = char;
using value_t = double;

class FunctionPart
{
private:
	operation_t operation {};
	value_t value {};
public:
	FunctionPart(const operation_t&,const value_t&);
	FunctionPart();
	void Invert();
	value_t Apply(const value_t&) const;
};


FunctionPart::FunctionPart()
{
}


FunctionPart::FunctionPart(const operation_t& new_operation,const value_t& new_value)
	: operation {new_operation}
	, value {new_value}
{
}


void FunctionPart::Invert()
{
	switch(operation)
	{
		case '+':
			operation = '-';
			break;
		case '-':
			operation = '+';
			break;
		case '*':
			operation = '/';
			break;
		case '/':
			operation = '*';
			break;
	}
}


value_t FunctionPart::Apply(const value_t& weight) const
{
	if(operation == '+')
		return weight + value;
	if(operation == '-')
		return weight - value;
	if(operation == '*')
		return weight * value;
	if(operation == '/')
		return weight / value;
	return 0;
}


//-----------------------------------------------------------


class Function
{
public:
	void AddPart(const operation_t&,const value_t&);
	void Invert();
	value_t Apply(value_t) const;
private:
	std::vector<FunctionPart> vParts {};
};


void Function::AddPart(const operation_t& operation,const value_t& value)
{
	vParts.push_back(FunctionPart(operation,value));
}


void Function::Invert()
{
	std::for_each(std::begin(vParts),std::end(vParts),[](decltype(vParts)::reference part){part.Invert();});
	std::reverse(std::begin(vParts),std::end(vParts));
}


value_t Function::Apply(value_t weight) const  
{
	std::for_each(std::cbegin(vParts),std::cend(vParts),[&weight](decltype(vParts)::const_reference part){ weight = part.Apply(weight);});
	return weight;
}

//------------------------------------------------------------------

void testFunction_DefaultConstruct()
{
	const auto upFunction = std::make_unique<Function>();
	assert(nullptr != upFunction);
}

void testFunctionPart_DefaultConstruct()
{
	const auto upFunction = std::make_unique<Function>();
	assert(nullptr != upFunction);
}

void testFunctionPart_ConstructWithTwoParams()
{
	const auto upFunction = std::make_unique<FunctionPart>('-',1.2);
	assert(nullptr != upFunction);
}

void testFunction_Apply()
{
	auto upFunction = std::make_unique<Function>();
	upFunction->AddPart('-',10);
	upFunction->AddPart('+',36);
	value_t weight {10};
	assert(36 == upFunction->Apply(weight));
}

void testFunction_Invert()
{
	auto upFunction = std::make_unique<Function>();
	upFunction->AddPart('-',10);
	upFunction->AddPart('+',36);
	upFunction->Invert();
	value_t weight {46};
	assert(20 == upFunction->Apply(weight));
}

void testFunction_Apply_Multiplication()
{
	auto upFunction = std::make_unique<Function>();
	upFunction->AddPart('*',4);
	upFunction->AddPart('-',4);
	upFunction->AddPart('+',36);
	value_t weight {10};
	assert(72 == upFunction->Apply(weight));
}

void testFunction_Apply_Invert()
{
	auto upFunction = std::make_unique<Function>();
	upFunction->AddPart('*',4);
	upFunction->AddPart('-',4);
	upFunction->AddPart('+',36);
	upFunction->Invert();
	value_t weight {52};
	assert(5 == upFunction->Apply(weight));
}




//-------------------------------------------------------------------
/*
int main()
{
	testFunctionPart_ConstructWithTwoParams();
	testFunctionPart_DefaultConstruct();
	testFunction_DefaultConstruct();
	testFunction_Apply();
	testFunction_Invert();
	testFunction_Apply_Multiplication();
	testFunction_Apply_Invert();
	return 0;
}
*/
