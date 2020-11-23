#include "gtest/gtest.h"
#include "equation.h"
#include <sstream>
#include <string>

TEST( Parser, OneNumber_OneOperation )
{
	std::istringstream is;
	is.str("8\n1\n* 3\n");
	Parser pr(is);
	std::ostringstream os;
	pr.GetEquation(os);
	std::string expectedResult {"(8) * 3"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST( Parser, OneNumber_OneOperation2 )
{
	std::istringstream is;
	is.str("8\n1\n- 3\n");
	Parser pr(is);
	std::ostringstream os;
	pr.GetEquation(os);
	std::string expectedResult {"(8) - 3"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST( Parser, OneNumber_ThreeOperations )
{
	std::istringstream is;
	is.str("8\n3\n* 3\n- 6\n/ 1");
	Parser pr(is);
	std::ostringstream os;
	pr.GetEquation(os);
	std::string expectedResult {"(((8) * 3) - 6) / 1"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST( Parser, OneNumber_ThreeOperations2 )
{
	std::istringstream is;
	is.str("8\n3\n* 3\n- -6\n/ 1");
	Parser pr(is);
	std::ostringstream os;
	pr.GetEquation(os);
	std::string expectedResult {"(((8) * 3) - -6) / 1"};
	EXPECT_EQ( os.str(), expectedResult );
} 
