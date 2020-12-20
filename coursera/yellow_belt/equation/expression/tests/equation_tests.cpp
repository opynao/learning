#include "gtest/gtest.h"
#include "equation_stack.h"
#include <sstream>
#include <string>

class ParserTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	std::istringstream is;
	std::ostringstream os;
};


TEST_F( ParserTest, OneNumber_OneOperation )
{
	is.str("8\n1\n* 3\n");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"8 * 3"};
	EXPECT_EQ( os.str(), expectedResult );
}

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
}

TEST_F( ParserTest, OneNumber_SixOperations )
{
	is.str("8\n6\n* 3\n- -6\n/ 1\n- 2\n/ 3\n* 4");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"((8 * 3 - -6) / 1 - 2) / 3 * 4"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST_F( ParserTest, Input_One_Line )
{
	is.str("1\n7\n+ 1 - 2 + 3 * 4 / 5 * 6 * 7");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"(1 + 1 - 2 + 3) * 4 / 5 * 6 * 7"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST_F( ParserTest, test1 )
{
	is.str("1\n7\n+ 1\n - 2\n + 3\n * 4\n / 5\n * 6\n * 7");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"(1 + 1 - 2 + 3) * 4 / 5 * 6 * 7"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST_F( ParserTest, test2 )
{
	is.str("8\n3\n* 1\n * 2\n * 3");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"8 * 1 * 2 * 3"};
	EXPECT_EQ( os.str(), expectedResult );
}

TEST_F( ParserTest, test3 )
{
	is.str("-3 2\n* -2\n+ 1");
	Parser pr(is);
	pr.GetEquation(os);
	std::string expectedResult {"-3 * -2 + 1"};
	EXPECT_EQ( os.str(), expectedResult );
}

