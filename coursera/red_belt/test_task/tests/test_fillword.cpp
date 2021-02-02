#include "gtest/gtest.h"
#include "fillword.h"
#include <vector>
/*
TEST( FillWord, Construct )
{
  FillWord fl( "QLGNAEKIRLRNGEAE", "KING" );
  std::vector<std::vector<char>> result 
  {
    {'Q','L','G','N'},
    {'A','E','K','I'},
    {'R','L','R','N'},
    {'G','E','A','E'}
  };
  EXPECT_EQ( fl.GetMatrixChars(), result );
}
*/
TEST( BuildSequence, BasicTest1 )
{
  LettersSequence fl( "QLGNAEKIRLRNGEAE", "KING" );
  std::vector<std::pair< size_t, size_t >> result 
  {
    { 1, 2},
    { 1, 3},
    { 0, 3},
    { 0, 2}
  };
  EXPECT_EQ( fl.Build() , result ); 
}

TEST( BuildSequence, BasicTest2 )
{
  LettersSequence fl( "ABCKLPMOWSTH", "LOW" );
  std::vector<std::pair< size_t, size_t >> result 
  {
    { 1, 1},
    { 2, 1},
    { 2, 2}
  };
  EXPECT_EQ( fl.Build() , result ); 
}
