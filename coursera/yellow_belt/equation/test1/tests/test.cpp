//#include "gtest/gtest.h"
#include "equation.h"
#include <sstream>
#include <string>
#include <cassert>
/*
class ParserTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	std::istringstream is;
	std::ostringstream os;
};

*/
//TEST( ParserTest, OneNumber_OneOperation )
void test1()
{
	std::istringstream is;
	std::ostringstream os;

	is.str("8\n1\n* 3\n");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"8 * 3"};
	assert( 1 == 1);
//
//EXPECT_EQ( os.str(), expectedResult );
}
/*
TEST_F( ParserTest, OneNumber_OneOperation2 )
{
	is.str("8\n1\n- 3\n");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"8 - 3"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST_F( ParserTest, OneNumber_ThreeOperations )
{
	is.str("8\n3\n* 3\n- 6\n/ 1");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"(8 * 3 - 6) / 1"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST_F( ParserTest, OneNumber_ThreeOperations2 )
{
	is.str("8\n3\n* 3\n- -6\n/ 1");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"(8 * 3 - -6) / 1"};
	EXPECT_EQ( os.str(), expectedResult );
} */
