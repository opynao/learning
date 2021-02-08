#include "split.h"
#include "gtest/gtest.h"

#include <vector>
#include <utility>

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
TEST( TestSplitting, Test1 ) 
{
  EXPECT_EQ( SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})), 
      std::vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}    
        })    
      );
  EXPECT_EQ( SplitIntoSentences( std::vector<TestToken>( {{"Split"}, {"into"}, {"sentences"}, {"!", true}} )),
            std::vector<Sentence<TestToken>>( { {{"Split"}, {"into"}, {"sentences"}, {"!", true}} }) );

  EXPECT_EQ( SplitIntoSentences( std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    std::vector<Sentence<TestToken>>( {
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

TEST( TestSplitting, Test2 )
{
   EXPECT_EQ( SplitIntoSentences( std::vector<TestToken>( { {"!", true}, {"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}} )),
    std::vector<Sentence<TestToken>>( {
        {{ "!",true },{ "!",true }},
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
    );
}

TEST( TestSplitting, Test3 )
{
   EXPECT_EQ( SplitIntoSentences( std::vector<TestToken>( { {"!", true}, {"!", true}, {"Split"}, {"into"}, {"sentences"}} )),
    std::vector<Sentence<TestToken>>( {
        {{ "!",true },{ "!",true }},
        {{"Split"}, {"into"}, {"sentences"}}
    })
    );
}

TEST( TestAvoidsCopying, Test )
{
  std::vector<NoncopyableString> b;
  b.reserve(4);
  b.emplace_back( "Split" );
  b.emplace_back( "into" );
  b.emplace_back( "sentences" );
  b.emplace_back( "!" );
  std::vector<Sentence<NoncopyableString>> result (1);
  result[0].reserve(4);
  result[0].emplace_back( "Split" );
  result[0].emplace_back( "into" );
  result[0].emplace_back( "sentences" );
  result[0].emplace_back( "!" );    
  EXPECT_EQ( SplitIntoSentences( std::move( b ) ), result ) ;
}
