#pragma once

#include "paginate.h"

#include <string>
#include <map>
#include <set>
#include <istream>

struct Stats
{
  std::map<std::string, size_t> word_frequences;

  void operator+=(const Stats &other);
};

//Stats ExploreLine(const std::set<std::string> &key_words, const std::string &line);

template <typename String>
Stats ExploreLine(const std::set<std::string> &key_words, const String &line)
{
  Stats result;
  for (auto &word : key_words)
  {
    std::string toFind = " " + word + " ";
    size_t pos = line.find(toFind);
    size_t count{};
    while (pos <= line.size())
    {
      ++count;
      pos = line.find(toFind, pos);
    }
    result.word_frequences[word] = count;
    PR(word);
    PR(count);
  }
  return result;
}

template <typename ContainerOfStrings>
Stats ExploreKeyWordsSingleThread(
    const std::set<std::string> &key_words,
    ContainerOfStrings &strings)
{
  LOGF;

  Stats result;
  for (auto &string : strings)
    result += ExploreLine(key_words, string);
  LOGF;

  return result;
}

Stats ExploreKeyWords(const std::set<std::string> &key_words, std::istream &input);
