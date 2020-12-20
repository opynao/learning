#include "equation.h"
#include <iostream>

int main()
{
	Parser pr(std::cin);
	pr.GetEquation(std::cout);
	return 0;
}

