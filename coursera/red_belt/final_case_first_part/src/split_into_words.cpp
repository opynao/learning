#include "split_into_words.h"

std::vector<std::string_view> SplitIntoWords(std::string_view line)
{
  std::vector<std::string_view> result;

  size_t pos = FindWordBeginning(line, 0);
  line.remove_prefix(pos);
  while (pos != line.npos)
  {
    pos = line.find(' ');
    result.push_back(line.substr(0, pos));
    pos = FindWordBeginning(line, pos);
    line.remove_prefix(pos);
  }
  return result;
}

size_t FindWordBeginning(std::string_view line, size_t pos)
{
  return line.find_first_not_of(' ', pos);
}