#include "parser.h"
#include <iterator>
#include <algorithm>


void Parser::Parse(std::istream& is)
{
    size_t vectorSize {};
    is >> vectorSize;
    ReadVector( is, vectorSize );
    size_t querySize {};
    is >> querySize;
    ReadQuery( is, querySize );
}

void Parser::ReadVector(std::istream& is, size_t vectorSize )
{
    std::copy_n( std::istream_iterator<int>( is ), vectorSize, std::back_inserter( m_Vector ) );
}

void Parser::ReadQuery(std::istream& is, size_t querySize)
{
    std::copy_n( std::istream_iterator<int>( is ), querySize, std::back_inserter( m_Query ) );
}

const std::vector<int>& Parser::GetVector() const
{
    return m_Vector;
}

const std::vector<int>& Parser::GetQuery() const
{
    return m_Query;
}

void Print( const Parser& pr, std::ostream& os )
{
    for( const auto& item : pr.GetQuery() )
    {
        const auto it = std::lower_bound( pr.GetVector().begin(), pr.GetVector().end(), item );
        const size_t index = std::distance( pr.GetVector().begin(), std::next(it) );
        os << (*it == item ? "Yes " : "No ") << index << std::endl;
    }
}
