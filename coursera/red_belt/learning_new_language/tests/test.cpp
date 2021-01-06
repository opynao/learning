#include "learn.h"
#include "gtest/gtest.h"
#include <sstream>

TEST( Learner, Test1 )
{
  Learner learner;
  std::string line;
  std::istringstream is ("apple apricot calendar cat ananas");
  std::ostringstream os;
  while (std::getline(is, line)) 
  {
      std::vector<std::string> words;
      std::stringstream ss(line);
      std::string word;
      while (ss >> word) 
      {
        words.push_back(word);
      }
      os << learner.Learn(words) << std::endl;
  }
  for (auto word : learner.KnownWords()) 
  {
      os << word << "\n";
  }
  EXPECT_EQ( os.str(), "5\nananas\napple\napricot\ncalendar\ncat\n");
}
