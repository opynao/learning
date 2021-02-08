#include "letters_sequence.h"

LettersSequence::LettersSequence( const Word_t& wordToSearch, const Word_t& givenWord )
  : wordToSearch_ { wordToSearch }
  , givenWord_ { givenWord }
{
  numberOfRows_ = std::sqrt( wordToSearch.size() );
}

const LettersSequence::lettersSequense_t LettersSequence::Build() const
{
  allLetters_t result;
  size_t posOfFindChar = 0;
  while( posOfFindChar <= wordToSearch_.size() )
  {
    lettersSequense_t v;
    posOfFindChar = wordToSearch_.find( givenWord_[0], posOfFindChar ); 
    result.push_back( v.push_back( CalculateRowColumn( posOfFindChar ) ) );
  }
  
//  char firstChar = givenWord_[1];
//  while( !CharIsNear( posOfFindChar, firstChar) )
//     posOfFindChar = wordToSearch_.find( firstChar, posOfFindChar );


  for( size_t i = 1; i != givenWord_.size(); ++i )
  {
    char chToFind = givenWord_[i];
    
    if( CheckNextPosition( (posOfFindChar + 1), chToFind ) )
    {
      ++posOfFindChar;
      result.push_back( CalculateRowColumn(posOfFindChar) );
    }
    
    else if( CheckNextPosition( (posOfFindChar - 1), chToFind ) )
    { 
      --posOfFindChar;
      result.push_back( CalculateRowColumn(posOfFindChar) );
    }
    
    else if( CheckNextPosition( (posOfFindChar - numberOfRows_), chToFind ) )
    {
      posOfFindChar -= numberOfRows_;
      result.push_back( CalculateRowColumn(posOfFindChar) );
    }
    
    else if( CheckNextPosition( ( posOfFindChar + numberOfRows_), chToFind ) ) 
    {
      posOfFindChar += numberOfRows_;
      result.push_back( CalculateRowColumn(posOfFindChar) );
    }
    else
    {
      result.clear();
      posOfFindChar = wordToSearch_.find( givenWord_[i - 1], posOfFindChar );
      result.push_back( CalculateRowColumn( posOfFindChar ) );
    }
  }
  return result;
}

bool LettersSequence::CharIsNear( const size_t pos, const char ch ) const 
{
  return CheckNextPosition( pos + 1, ch ) || CheckNextPosition( pos - 1, ch ) || CheckNextPosition( pos + numberOfRows_, ch ) || CheckNextPosition( pos - numberOfRows_, ch );
}

bool LettersSequence::CheckNextPosition( const size_t pos, const char ch ) const
{
  return wordToSearch_[pos] == ch;
}

const std::pair< size_t, size_t > LettersSequence::CalculateRowColumn( const size_t posOfFindChar ) const
{
  size_t row = posOfFindChar / numberOfRows_;
  size_t column = posOfFindChar % numberOfRows_;
  PR(row);
  PR(column);
  return { row, column };
}
