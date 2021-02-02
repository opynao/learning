#pragma once
#include "build_sequence.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

class LettersSequence 
{
public:
//  using MatrixChars_t = std::vector< std::vector< char >>;
  using lettersSequense_t = std::vector< std::pair< size_t, size_t >>;
public:
/*  FillWord( const std::string& str, const std::string& givenWord )
    : givenWord_ { givenWord }
  {
    size_t numberOfRows = std::sqrt( str.size() );
    for( size_t i = 0; i != str.size(); i += numberOfRows )
    {
      std::vector< char > vec;
      vec.reserve( numberOfRows );
      for( size_t j = i; j != ( i + numberOfRows ); ++j )
        vec.push_back( str[j] );
      matrixChars_.push_back( vec );
    }
  }
*/
  LettersSequence( const std::string& wordToSearch, const std::string& givenWord )
    : wordToSearch_ { wordToSearch }
    , givenWord_ { givenWord }
  {}

/*  MatrixChars_t GetMatrixChars() const
  {
    return matrixChars_;
  }
*/  
  lettersSequense_t Build() 
  {
   size_t numberOfRows = std::sqrt( wordToSearch_.size() );
   lettersSequense_t result;
   size_t posOfFindChar = wordToSearch_.find( givenWord_[0] ); 
   result.push_back( CalculateRowColumn( posOfFindChar ) );

   for( size_t i = 1; i != givenWord_.size(), ++i )
   {
      char chToFind = givenWord_[i];
      
      if( CheckNextPosition( posOfFindChar + 1 ) )
      {
        ++posOfFindChar;
        result.push_back( CalculateRowColumn(posOfFindChar) );
      }
      
      else if( CheckNextPosition( posOfFindChar - 1) )
      { 
        --posOfFindChar;
        result.push_back( CalculateRowColumn(posOfFindChar) );
      }
      
      else if( CheckNextPosition( posOfFindChar - numberOfRows) )
      {
        posOfFindChar -= numberOfRows;
        result.push_back( CalculateRowColumn(posOfFindChar) );
      }
      
      else if( CheckNextPosition( posOfFindChar + numberOfRows) )
      {
        posOfFindChar += numberOfRows;
        result.push_back( CalculateRowColumn(posOfFindChar) );
      }
    }
  //  BuildSequence buildSequense( matrixChars_, givenWord_ );
  //  return buildSequense.GetSequence();
    return result;
  }
    
bool CheckNextPosition( size_t pos, char ch )
{
  return wordToSearch_[pos] == ch;
}

std::pair< size_t, size_t > CalculateRowColumn( size_t posOfFindChar )
{
  size_t row = posOfFindChar / numberOfRows;
  size_t column = posOfFindChar % numberOfRows;
  return { row, column };
}

private:
  std::string wordToSearch_;
  std::string givenWord_;
//  MatrixChars_t matrixChars_;
//  lettersSequense_t lettersSequense_;
};
