#pragma once
#include <iostream>
#include <vector>
#include <utility>

class Parser
{
public:
    Parser() {}
    using vector_t = std::vector<std::vector<int>>;
    using query_t = std::vector<std::pair<int,int>>;
    void Parse( std::istream& );
    void MakeVector( std::istream&, size_t );
    void MakeQuery( std::istream&, size_t );
    const vector_t& GetVector() const;
    const query_t& GetQuery() const;
private:
    vector_t m_Vector;
    query_t m_Query;
};

void Print( const Parser&, std::ostream& ); 
