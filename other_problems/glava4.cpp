#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>
#include <array>
#include <algorithm>
#include <iterator>

std::vector<std::string> testInputs {
	{"10 20|"},
	{"10 20 |"},
	{"10|"},
	{"10|20"},
	{"|"},
	{"10 20 30 40 |"}
};

class NumberCollector

void InputOutputNumbers( std::istream& istream , std::ostream& ostream )
{
	std::array<int, 2> aNumbers;
	while ( istream.peek() != '|' && std::isdigit( istream.peek() ) || !istream.get() )
	{
		auto readNumber = []( std::istream& is )
		{
			return [&is]( int& rNumber )
			{
				is >> rNumber;
			};	
		};
		auto writeNumber = []( std::ostream& os )
		{
			return [&os]( const int& rNumber )
			{
				std::ostream_iterator<int> it( os, " " );
				*it = rNumber;
			};
		};
		std::for_each( aNumbers.begin(), aNumbers.end(), readNumber( istream ) );
		std::for_each( aNumbers.begin(), aNumbers.end(), writeNumber( ostream ) );

	}
	return;
}

bool RunTests()
{
	std::stringstream ostream;
	
	std::stringstream istream1( testInputs[0] ); 
	InputOutputNumbers( istream1, ostream );
	int a {};
	int b {};
	ostream >> a >> b;
	assert( a == 10 );
	assert( b == 20 );
	
	std::stringstream istream2( testInputs[1] ); 
	InputOutputNumbers( istream2, ostream );
	a = b = 0;
	ostream >> a >> b;
	assert( a == 10 );
	assert( b == 20 );

	ostream.clear();
	std::stringstream istream3( testInputs[2] ); 
	std::stringstream ostream1;
	InputOutputNumbers( istream3, ostream1 );
	std::cerr << ostream1.tellp() << std::endl;
	assert( ostream1.tellp() == 0 );


	return true;
}

int main(int argc, char** argv)
{
	if ( argc > 1 )
	{
		if ( std::string(argv[1]) != "tests" )
		{
 	        	std::cout << argv[0] << " tests\t for run tests  " << std::endl;
			return 1; 
       		}
		else
		{
			return RunTests();
		}
	}

		
	return 0;
}


