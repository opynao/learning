#pragma once
#include <sstream>
#include <vector>
#include <string>

class Printer
{
public:
    void Push(const std::string &str, const int medianAge);

    std::ostringstream Print() const;

private:
    std::vector<std::pair<std::string, int>> m_info;
};