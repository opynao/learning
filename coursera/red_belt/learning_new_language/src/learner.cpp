#include "learn.h"
#include <algorithm>

int Learner::Learn(const std::vector<std::string>& words) 
{
  int newWords = 0;
  for (const auto& word : words) 
  {
    if (!dict.count(word)) 
    {
      ++newWords;
      dict.insert(word);
    }
  }
  return newWords;
}

std::vector<std::string> Learner::KnownWords()
{
  return { dict.begin(), dict.end() };
}
