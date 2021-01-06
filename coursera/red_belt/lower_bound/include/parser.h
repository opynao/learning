#pragma once
#include <iostream>
#include <vector>

class Parser
{
public:
    void Parse(std::istream&);
    void ReadVector(std::istream&, size_t);
    void ReadQuery(std::istream&, size_t);
    const std::vector<int>& GetVector() const;
    const std::vector<int>& GetQuery() const;
private:
    std::vector<int> m_Vector;
    std::vector<int> m_Query;
};

void Print( const Parser&, std::ostream& );
