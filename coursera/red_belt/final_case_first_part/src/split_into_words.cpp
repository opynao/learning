#include "split_into_words.h"
#include "search_server.h"

#include <iterator>
#include <sstream>
/*
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
*/

std::vector<std::string> SplitIntoWords(const std::string &line)
{
  std::vector<std::string> result;
  std::istringstream iss(line);
  std::move(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(result));
  //for (std::string current_string; std::getline(iss, current_string, ' ');)
  //  result.push_back(std::move(current_string));
  return result;
}

size_t FindWordBeginning(std::string_view line, size_t pos)
{
  return line.find_first_not_of(' ', pos);
}