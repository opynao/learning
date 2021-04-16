#include <string>
#include <map>
#include <set>
#include <istream>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <iostream>
#include <future>
#include <functional>
#include <deque>

using namespace std;

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
        if (count != 0U)
            result.word_frequences[str] += count;
    }
    return result;
}

Stats ExploreKeyWords(const std::set<std::string> &key_words, std::istream &input)
{
  std::vector<std::future<Stats>> futures;
  std::deque<std::string> inputStr;
  Stats stats;
  std::string line{};

  while (input >> line)
    inputStr.push_back(std::move(line));
  
  size_t bunch_size = inputStr.size() / 4;
  std::vector<std::vector<std::string>> strings{};
  strings.reserve(5);
  
  std::vector<std::string> vec{};
  vec.reserve(bunch_size);
  
  for (size_t i = 0; i < inputStr.size(); i += bunch_size)
  {
    auto last = std::min(inputStr.size(), i + bunch_size);
    std::move(inputStr.begin() + i, inputStr.begin() + last, back_inserter(vec));
    strings.push_back(vec);
    vec.clear();
  }
  for (auto& string : strings)
    futures.push_back(std::async([=] { return ExploreKeyWordsSingleThread(std::ref(key_words), string); }));

  for (auto &future : futures)
    stats += future.get();

  return stats;
}

void Stats::operator+=(const Stats &other)
{
    for (auto &word_frequency : other.word_frequences)
        word_frequences[word_frequency.first] += word_frequency.second;
}

int main()
{
    return 0;
}