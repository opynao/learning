#include "parser.h"
#include "gtest/gtest.h"

class ReadingManagerTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    os.str("");
  }
 ReadingManager rm;
 std::ostringstream os;
};

TEST_F( ReadingManagerTest, ComplexTest )
{
  std::istringstream is("12\nCHEER 5\nREAD 1 10\nCHEER 1\nREAD 2 5\nREAD 3 7\nCHEER 2\nCHEER 3\nREAD 3 10\nCHEER 3\nREAD 3 11\nCHEER 3\nCHEER 1\n");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n1\n0\n0.5\n0.5\n1\n0.5\n" );
}

TEST_F( ReadingManagerTest, PersonNotExist )
{
  std::istringstream is("1\nCHEER 5");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n" );
}

TEST_F( ReadingManagerTest, PersonNotExist2 )
{
  std::istringstream is("2\nREAD 1 3\nCHEER 5");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n" );
}

TEST_F( ReadingManagerTest, PersonIsUnique )
{
  std::istringstream is("2\nREAD 1 3\nCHEER 1");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "1\n" );
}

TEST_F( ReadingManagerTest, PersonNotUnique )
{
  std::istringstream is("3\nREAD 1 3\nREAD 2 5\nCHEER 2");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "1\n" );
}

TEST_F( ReadingManagerTest, UniquePerson )
{
  std::istringstream is("4\nREAD 1 0\nREAD 1 5\nREAD 2 4\nCHEER 1");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "1\n" );
}

TEST_F( ReadingManagerTest, PersonWithZeroPage )
{
  std::istringstream is("3\nREAD 1 0\nREAD 1 1\nCHEER 1");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "1\n" );
}

TEST_F( ReadingManagerTest, UniquePerson2 )
{
  std::istringstream is("4\nREAD 1 0\nREAD 1 5\nREAD 2 4\nCHEER 2");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n" );
}

TEST_F( ReadingManagerTest, UniquePerson3 )
{
  std::istringstream is("5\nREAD 1 0\nREAD 1 5\nREAD 2 5\nCHEER 2\nCHEER 1");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n0\n" );
}

TEST_F( ReadingManagerTest, SomePersonsReadZeroPages )
{
  std::istringstream is("5\nREAD 1 0\nREAD 2 0\nREAD 3 0\nREAD 4 1\nCHEER 4\n");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n" );

}

TEST_F( ReadingManagerTest, UniquePerson4 )
{
  std::istringstream is("5\nREAD 1 0\nREAD 1 5\nREAD 2 4\nREAD 3 7\nCHEER 1\n");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0.5\n" );
}

TEST_F( ReadingManagerTest, SomeUsersWithTheSamePageCount )
{
  std::istringstream is("6\nREAD 6 5\nREAD 2 5\nREAD 1 5\nREAD 3 4\nREAD 4 5\nCHEER 2\n");
  Parser pr( is, os, rm );
  pr.Parse();
  EXPECT_EQ( os.str(), "0.25\n" );
}


