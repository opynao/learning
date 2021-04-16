#pragma once

#include <string>
#include <map>
#include <set>
#include <istream>

struct Stats
{
  std::map<std::string, int> word_frequences;

  void operator+=(const Stats &other);
};

template <typename ContainerOfStrings>
Stats ExploreKeyWordsSingleThread(
    const std::set<std::string> &key_words,
    ContainerOfStrings &strings)
{
  Stats result;

  for (const auto &str : strings)
  {
    size_t count = key_words.count(str);
    if ( count != 0U)
      result.word_frequences[str] += count;
  }
  return result;
}

Stats ExploreKeyWords(const std::set<std::string> &key_words, std::istream &input);
