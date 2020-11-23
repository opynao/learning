#include "gtest/gtest.h"
#include "find_started_from_char.h"
#include <iostream>
using namespace std;

TEST( FindFromChar, Vector_Contains_StringsWithChar)
{
	const std::vector<std::string> sorted_strings {"moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'm');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {"moscow", "murmansk"};
	EXPECT_EQ( resultOfFind, result );
}

TEST( FindFromChar, Vector_Contains_OneStringWithChar)
{
	const std::vector<std::string> sorted_strings {"moscow"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'm');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {"moscow"};
	EXPECT_EQ( resultOfFind, result );
}

TEST( FindFromChar, Vector_Contains_OneStringWithoutChar)
{
	const std::vector<std::string> sorted_strings {"moscow"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'p');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 1);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 1);
}

TEST( FindFromChar, Vector_Contains_TwoStringsWithChar)
{
	std::vector<std::string> sorted_strings {"moscow", "murmansk","","",""};
	std::sort(sorted_strings.begin(),sorted_strings.end());
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'm');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {"moscow", "murmansk"};
	EXPECT_EQ( resultOfFind, result );
}


TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar)
{
	const std::vector<std::string> sorted_strings {"moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'p');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 2);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 2);
}

TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar2)
{
	const std::vector<std::string> sorted_strings {"moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'z');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 3);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 3);
}

TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar4)
{
	const std::vector<std::string> sorted_strings {"a", "aba","aca","cda","moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'b');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 3);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 3);
}

TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar5)
{
	const std::vector<std::string> sorted_strings {"","","","",""};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'b');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 5);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 5);
}



TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar3)
{
	const std::vector<std::string> sorted_strings {"mahachkala", "moscow", "murmansk","vitebsk","vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'm');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {"mahachkala", "moscow", "murmansk"};
	EXPECT_EQ( resultOfFind, result );
}


TEST( FindFromChar, EmptyVector)
{
	const std::vector<std::string> sorted_strings {};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), 'z');
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 0);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 0);
}


int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
