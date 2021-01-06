#include <string>
#include <vector>
#include <set>
#include <algorithm>

class Learner 
{
public:
  int Learn(const std::vector<std::string>& words); 
  std::vector<std::string> KnownWords();
private:
  std::set<std::string> dict;
  std::vector<std::string> v_dict;
};

int Learner::Learn(const std::vector<std::string>& words) 
{
  int newWords = 0;
  for (const auto& word : words) 
  {
    if (!dict.count(word)) 
    {
      ++newWords;
      dict.insert(word);
      v_dict.push_back(word);
    }
  }
  return newWords;
}

std::vector<std::string> Learner::KnownWords()
{
  std::sort(v_dict.begin(), v_dict.end());
  return v_dict;
}

int main()
{
  return 0;
}
