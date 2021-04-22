#pragma once
#include <string>
#include <sstream>
#include <set>

class Pangram
{
public:
    bool CheckIfPangram(const std::string &str)
    {
        char ch;
        const size_t sizeOfAlphabet{26};
        std::istringstream iss(str);
        while (iss)
        {
            iss >> ch;
            allStrings_.insert(ch);
        }
        return (allStrings_.size() == sizeOfAlphabet);
    }

private:
    std::set<char> allStrings_;
};