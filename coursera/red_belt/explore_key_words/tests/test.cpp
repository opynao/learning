#include "gtest/gtest.h"
#include "explore.h"
#include "paginate.h"

#include <set>
#include <string>
#include <sstream>

TEST(Test, Basic)
{
  const std::set<std::string> key_words = {"yangle", "rocks", "sucks", "all"};

  std::stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
  LOGF;
  const auto stats = ExploreKeyWords(key_words, ss);
  LOGF;
  const std::map<std::string, int> expected =
      {
          {"yangle", 6},
          {"rocks", 2},
          {"sucks", 1}};
  EXPECT_EQ(stats.word_frequences, expected);
}
