#include "gtest/gtest.h"
#include "find_started_from_char.h"
#include <iostream>

TEST( FindFromChar, Vector_Contains_StringsWithChar)
{
	const std::vector<std::string> sorted_strings {"moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar( std::begin(sorted_strings), std::end(sorted_strings), "mo" );
	const std::vector<std::string> resultOfFind( m_result.first, m_result.second );
	const std::vector<std::string> result {"moscow"};
	EXPECT_EQ( resultOfFind, result );
}

TEST( FindFromChar, Vector_Contains_StringsWithChar2)
{
	const std::vector<std::string> sorted_strings {"moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar( std::begin(sorted_strings), std::end(sorted_strings), "mt" );
	const std::vector<std::string> resultOfFind( m_result.first, m_result.second );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 1);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 1);
}


TEST( FindFromChar, Vector_Contains_OneStringWithChar)
{
	const std::vector<std::string> sorted_strings {"moscow"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "mo");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {"moscow"};
	EXPECT_EQ( resultOfFind, result );
}

TEST( FindFromChar, Vector_Contains_OneStringWithoutChar)
{
	const std::vector<std::string> sorted_strings {"moscow"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "p");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 1);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 1);
}

TEST( FindFromChar, Vector_Contains_TwoStringsWithChar)
{
	const std::vector<std::string> sorted_strings {"","","","moscow", "murmansk"};
	const auto m_result = FindStartsWithChar(std::begin(sorted_strings), std::end(sorted_strings), "m");
	const std::vector<std::string> resultOfFind (m_result.first, m_result.second);
	const std::vector<std::string> result {"moscow", "murmansk"};
	EXPECT_EQ( resultOfFind, result );
}


TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar)
{
	const std::vector<std::string> sorted_strings {"moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "pol");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 2);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 2);
}

TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar2)
{
	const std::vector<std::string> sorted_strings {"moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "zala");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 3);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 3);
}

TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar4)
{
	const std::vector<std::string> sorted_strings {"a", "aba","aca","cda","moscow", "murmansk", "vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "bir");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 3);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 3);
}

TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar5)
{
	const std::vector<std::string> sorted_strings {"","","","",""};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "b");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 5);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 5);
}



TEST( FindFromChar, Vector_DoesNt_Contain_StringsWithChar3)
{
	const std::vector<std::string> sorted_strings {"malachkala", "mascow", "murmansk","vitebsk","vologda"};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "ma");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {"malachkala", "mascow"};
	EXPECT_EQ( resultOfFind, result );
}


TEST( FindFromChar, EmptyVector)
{
	const std::vector<std::string> sorted_strings {};
	const auto m_result = FindStartsWithChar(begin(sorted_strings), end(sorted_strings), "zi");
	const std::vector<std::string> resultOfFind(m_result.first, m_result.second);
	const std::vector<std::string> result {};
	EXPECT_EQ( resultOfFind, result );
	EXPECT_EQ( m_result.first - std::cbegin(sorted_strings), 0);
	EXPECT_EQ( m_result.second - std::cbegin(sorted_strings), 0);
}

