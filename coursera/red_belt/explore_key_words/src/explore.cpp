#include "explore.h"
#include "paginate.h"

#include <future>
#include <functional>

void Stats::operator+=(const Stats &other)
{
  for (auto &word_frequency : other.word_frequences)
    word_frequences[word_frequency.first] += word_frequency.second;
}

Stats ExploreKeyWords(const std::set<std::string> &key_words, std::istream &input)
{
  LOGF;
  std::vector<std::future<Stats>> futures;
  std::vector<std::string> inputStr;
  //std::vector<std::vector<std::string>> strings;
  Stats stats;
  LOGF;

  for (std::string line; getline(input, line);)
  {
    LOGF;
    inputStr.push_back(line);
  }
  LOGF;
/*  for(size_t i = 0; i != inputStr.size()/4; ++i )
  {
    strings.
  }*/
  size_t pageSize = 1000;
  for (auto string : Paginate(inputStr, pageSize))
  {
    LOGF;
    futures.push_back(std::async([=] { return ExploreKeyWordsSingleThread(key_words, string); }));
  }
  LOGF;

  for (auto &future : futures)
  {
    LOGF;
    stats += future.get();
    LOGF;
  }
  LOGF;

  return stats;
}
