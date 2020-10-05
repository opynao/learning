#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

void quadraticEquation(double a, double b, double c, double& result1, double& result2);

void quadraticEquation(double a, double b, double c, double& result1, double& result2)
{
	if ( a == 0 && b == 0 )
	{
		throw std::out_of_range{"_a_ and _b_ coefficients are nules."};
	}

	if ( a == 0)
	{
		result1 = result2 = - c / b;
		return;
	}

	double diskriminant = pow( b,2 ) - 4 * a * c ;
	double delim = 2 * a ;
	double commonRoot = -b / delim;
	
	if( diskriminant < 0 )
	{
		throw std::out_of_range{"D is negative"};
	}	
	else if ( diskriminant == 0)
	{
		result1 = result2 = commonRoot;
	}
	else
	{
		double coef = std::sqrt( diskriminant ) / delim;
		result1 =  commonRoot + coef;
		result2 =  commonRoot - coef;
	}
}

int main()
{
	std::vector<double> aCoefficients;
	std::copy(std::istream_iterator<double>(std::cin),std::istream_iterator<double>(),std::back_inserter(aCoefficients));
	std::pair<double,double> roots {};
	try
	{
	 	quadraticEquation(aCoefficients[0],aCoefficients[1],aCoefficients[2],roots.first,roots.second);
	}
	catch(...)
	{ 
		return 0;
	}
	std::cout << roots.first;
	if(roots.first!=roots.second)
		std::cout << " " << roots.second;	
	return 0;
}
