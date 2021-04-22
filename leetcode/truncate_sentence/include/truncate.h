#pragma once
#include <string>
#include <sstream>

class Solution
{
public:
    std::string truncateSentence(const std::string &s, int k)
    {
        std::string result{};
        std::istringstream iss(s);
        for (std::string current_string; std::getline(iss, current_string, ' ') && k != 0; --k)
            result += current_string + ' ';
        result.pop_back();
        return result;
    }
};