#include "gtest/gtest.h"
#include "letters_sequence.h"
#include <vector>

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

TEST( BuildSequence, FirstCharInFirstRow )
{
  LettersSequence fl( "KLPMOWSTH", "LOW" );
  std::vector<std::pair< size_t, size_t >> result 
  {
    { 0, 1},
    { 1, 1},
    { 1, 2}
  };
  EXPECT_EQ( fl.Build() , result ); 
}

TEST( BuildSequence, FirstCharInLastRow )
{
  LettersSequence fl( "KABMWOHTL", "LOW" );
  std::vector<std::pair< size_t, size_t >> result 
  {
    { 2, 2},
    { 1, 2},
    { 1, 1}
  };
  EXPECT_EQ( fl.Build() , result ); 
}

TEST( BuildSequence, TwoSameCharsNearOne )
{
  LettersSequence fl( "BALOAEVOAABAAAABAAAABAAAA", "LOVE" );
  std::vector<std::pair< size_t, size_t >> result 
  {
    { 0, 2},
    { 1, 2},
    { 1, 1},
    { 1, 0}
  };
  EXPECT_EQ( fl.Build() , result ); 
}

TEST( BuildSequence, TwoSameCharsNearOne2 )
{
  LettersSequence fl( "KLOVOHETK", "LOVE" );
  std::vector<std::pair< size_t, size_t >> result 
  {
    { 0, 1},
    { 1, 1},
    { 1, 0},
    { 2, 1}
  };
  EXPECT_EQ( fl.Build() , result ); 
}

TEST( BuildSequence, TwoSameFirstChars )
{
  LettersSequence fl( "KLPMNTLSHOWN", "LOW" );
  std::vector<std::pair< size_t, size_t >> result 
  {
    { 2, 0},
    { 3, 0},
    { 3, 1}
  };
  EXPECT_EQ( fl.Build() , result ); 
}
