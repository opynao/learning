#include "parser.h"
#include <iterator>
#include <algorithm>
void Parser::Parse(std::istream& is)
{
    size_t numberOfArrays, numberOfQueries;
    is >> numberOfArrays;
    is >> numberOfQueries;
    MakeVector( is, numberOfArrays );
    MakeQuery( is, numberOfQueries );
}

void Parser::MakeVector( std::istream& is, size_t numberOfArrays )
{
    m_Vector.resize( numberOfArrays );
    for( size_t i = 0; i != numberOfArrays ; ++i)
    {
        size_t sizeOfArray {};
        is >> sizeOfArray;
        m_Vector[i].reserve( sizeOfArray );
        std::copy_n( std::istream_iterator<int>( is ), sizeOfArray, std::back_inserter( m_Vector[i] ) );
   }
}

void Parser::MakeQuery( std::istream& is, size_t numberOfQueries )
{
   int first, second;
   while( numberOfQueries-- )
   {
       is >> first;
       is >> second;
       m_Query.emplace_back(first,second);
   }
}

const Parser::vector_t& Parser::GetVector() const
{
    return m_Vector;
}

const Parser::query_t& Parser::GetQuery() const
{
    return m_Query;
}

void Print(const Parser& pr, std::ostream& os) 
{
    for( const auto& item : pr.GetQuery() )
        os << pr.GetVector()[item.first][item.second] << std::endl;
}

