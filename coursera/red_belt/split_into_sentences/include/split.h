#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

template < typename Token >
using Sentence = std::vector< Token >;

template< typename TokenForwardIt >
TokenForwardIt FindSentenceEnd( TokenForwardIt tokens_begin, TokenForwardIt tokens_end )
{
  const TokenForwardIt before_sentence_end = std::adjacent_find( tokens_begin, tokens_end, 
      []( const auto& left_token, const auto& right_token )
      {
        return left_token.IsEndSentencePunctuation() && !right_token.IsEndSentencePunctuation();
      });
  return before_sentence_end == tokens_end ? tokens_end : std::next( before_sentence_end );
}

template < typename Token >
std::vector< Sentence< Token >> SplitIntoSentences( std::vector< Token > tokens) 
{
  std::vector< Sentence< Token >> sentences;
  auto tokens_begin = std::begin( tokens );
  const auto tokens_end = std::end( tokens );
  while( tokens_begin != tokens_end )
  {
    const auto sentence_end = FindSentenceEnd( tokens_begin, tokens_end );
    Sentence< Token > sentence( 
        make_move_iterator( tokens_begin ),
        make_move_iterator( sentence_end )
        );
    tokens_begin = sentence_end;
    sentences.push_back( std::move(sentence) );
  }
  return sentences;
}

/*
template < typename Token >
std::vector< Sentence< Token >> SplitIntoSentences( std::vector< Token > tokens) 
{
  std::vector< Sentence< Token >> result;
  typename std::vector< Token >::iterator itPrev = tokens.begin();
  for( auto itCur = tokens.begin(); itCur != tokens.end(); ++itCur )
  {
    if( EndOfTokens( tokens, itCur ) )
    {
      ++itCur;
      BuildSentence( result, itPrev, itCur );
      break;
    }
    
    if( IsSentenceEnd( itCur ) ) 
    {
      itCur = CheckNextPunctuationMark( itCur );
      BuildSentence( result, itPrev, itCur );
      itPrev = itCur;
    }
    else
      continue;
  }
  return result;
}

template< typename Token >
bool EndOfTokens( std::vector< Token >& tokens, typename std::vector< Token >::iterator itCur )
{
  return itCur == std::prev( tokens.end() );
}

template< typename It >
It CheckNextPunctuationMark( It itCur )
{
   auto itTmp = itCur;
    
   while( IsSentenceEnd( itTmp ) )
      ++itTmp;
   return itTmp;
}

template< typename It >
bool IsSentenceEnd( It it )
{
  return it->IsEndSentencePunctuation();
}

template< typename Token >
void BuildSentence( std::vector< Sentence< Token >>& result, typename std::vector< Token >::iterator itPrev, typename std::vector< Token >::iterator itCur )
{
   std::vector< Token > sentence;
   sentence.reserve( std::distance( itPrev, itCur ) );
   std::move( itPrev, itCur, std::back_inserter( sentence) );
   result.push_back( std::move( sentence ) );
}
*/

struct TestToken 
{
  std::string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const 
  {
    return is_end_sentence_punctuation;
  }
  
  bool operator==(const TestToken& other) const 
  {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

std::ostream& operator<<( std::ostream& stream, const TestToken& token ) 
{
  return stream << token.data;
}

struct NoncopyableString
{
  std::string value_;
  bool is_end_sentence_punctuation = false;

  NoncopyableString( const std::string& value )
    : value_( value )
  {
    std::cout << "string copy\n";
  }

  NoncopyableString( std::string&& value )
    : value_( std::move(value) )
  {
     std::cout << "string move\n";
  }

  NoncopyableString( const NoncopyableString& other) 
    : value_ { other.value_ }
  {
    std::cout << "Copy ctor\n";
    PR(value_);
  }
  NoncopyableString& operator=( const NoncopyableString& other)
  {
   value_ = other.value_;
   std::cout << "Copy assign\n";
   return *this;
  }

  NoncopyableString( NoncopyableString&& other)
    : value_ { std::move( other.value_ ) }
  {
    std::cout << "Move ctor\n";
  }

  NoncopyableString& operator=( NoncopyableString&& other )
  {
    value_ = std::move( other.value_ );
    std::cout << "Move operator\n"; 
    return *this;
  }

  bool IsEndSentencePunctuation() const
  {
    return is_end_sentence_punctuation;
  }
};

bool operator == ( const NoncopyableString& lhs, const NoncopyableString& rhs )
{
  return lhs.value_ == rhs.value_;
}
