#include "gtest/gtest.h"
#include <iostream>

class Expression
{
public:
	Expression()
		: left_ {}
		, right_ {}
		, op_ {}
	{}

	Expression(Expression& left, const char op, Expression& right)
		: left_ {left}
		, op_ {op}
		, right_ {right}
		, number_ {}
	{}

	Expression(const int number)
		: number_ {number}
		, bIsNumber_ {true}
		, op_ {}
	{}

	virtual Expression& Get() const
	{
		
	}

	Expression left_ {};
	Expression right_ {};
	const char op_;
	int number_;
	bool bIsNumber_ {false};
};

std::ostream& operator << (std::ostream& os, const Expression& e)
{
	if(e.bIsNumber_)
		os << e.number_;
	else
		os << "(" << e.left_ << e.op_ << e.right_ << ")";
}


int main()
{
	Expression e(42);
	Expression e2(5,'-'6);
	Expression e3(e,'/',e2);
	std::cout << e3;
	return 0;
}
