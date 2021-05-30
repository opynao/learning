#include "printer.h"

void Printer::Push(const std::string &str, const int medianAge)
{
    m_info.emplace_back(str, medianAge);
}

std::ostringstream Printer::Print() const
{
    std::ostringstream oss;
    for (const auto &info : m_info)
        oss << info.first << info.second << "\n";
    return oss;
}