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
    Sentence< Token > sentence;
    for(; tokens_begin != sentence_end; ++tokens_begin )
      sentence.push_back( std::move(*tokens_begin));
    sentences.push_back( std::move(sentence) );
  }
  return sentences;
}

int main()
{
	return 0;
}
