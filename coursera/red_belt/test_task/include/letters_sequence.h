#pragma once
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

class LettersSequence 
{
public:
  using lettersSequense_t = std::vector< std::pair< size_t, size_t >>;
  using allLetters_t = std::vector< lettersSequense_t >;
  using Word_t = std::string;

public:
  LettersSequence( const Word_t&, const Word_t& );

  const lettersSequense_t Build() const;

private:
  bool CheckNextPosition( const size_t pos, const char ch ) const;

  const std::pair< size_t, size_t > CalculateRowColumn( const size_t posOfFindChar ) const;
  
  bool CharIsNear( const size_t pos, const char ch ) const;

private:
  Word_t wordToSearch_;
  Word_t givenWord_;
  size_t numberOfRows_;
};
