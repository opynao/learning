#include <array>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <algorithm>
#include <variant>

void quadraticEquation(double a, double b, double c, double& result1, double& result2);
using ReturnTypes = std::variant<std::pair<double, double>, std::exception>;
using TestDatas = std::vector
<
	std::pair
	<
		std::array<double,3>,
		ReturnTypes
	>
>;

void RunTest( TestDatas::reference rV )
{
	static int testNum = 0;
	std::cerr<< "TestNum = " << testNum++ << std::endl;
	double result1 {};
	double result2 {};
	if ( rV.second.index() == 0 )
	{
		quadraticEquation(rV.first[0],rV.first[1],rV.first[2],result1, result2);
		assert( fabs( result1 - std::get<0>(rV.second).first ) < 0.0001 );
		assert( fabs( result2 - std::get<0>(rV.second).second ) < 0.0001 );
	}
	else 
	{
		try
		{
			quadraticEquation(rV.first[0],rV.first[1],rV.first[2],result1, result2);
		}
		catch(std::out_of_range&)
		{
			return;
		}
		catch(...)
		{
		}
		assert(false);
	}
}
void RunTests()
{
	TestDatas vTestData
       	{
		{ { 1, 2, -6 }, ReturnTypes( std::make_pair( 1.64575, -3.64575 ) ) },
		{ { 1, -4, 4 }, ReturnTypes( std::make_pair(  2, 2 ) ) },
		{ { 0, 2, 2 }, ReturnTypes( std::make_pair ( -1, -1 ) ) },
		{ { 1, -6, 13 }, ReturnTypes( std::out_of_range("") ) },
		{ { 0, 0, 4 }, ReturnTypes( std::out_of_range("") ) }
	};
	std::for_each( vTestData.begin(), vTestData.end(), RunTest);
}

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

int main( int argc, char ** argv )
{
	if ( argc == 2 && std::string(argv[1]) == "tests" )
	{
		RunTests();
		return 0;
	}
	double a {};
	double b {};
	double c {};
	double result1 {};
	double result2 {};
	std::cout << "Quadratic equation has standard form ax2 + bx + c = 0. Please, enter the _a_ coefficient of the equation." << std::endl;
	std::cin >> a;
	std::cout << "Enter the _b_ coefficient of the equation." << std::endl;
	std::cin >> b;
	std::cout << "Enter the _c_ coefficient of the equation." << std::endl;
	std::cin >> c;
	try
	{
		quadraticEquation( a,b,c,result1,result2 );
		std::cout << "The first result is: " << result1 << std::endl;
		std::cout << "The second result is: " << result2 << std::endl;
	}
	catch(std::out_of_range& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
