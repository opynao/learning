#include <utility>
#include <vector>
#include <algorithm> 
#include <iostream>

template<typename T>
class Table
{
public:
  Table( const size_t l, const size_t c );
  void Resize( const size_t l, const size_t c );
  std::pair<size_t, size_t> Size() const;
  std::vector<T>& operator[]( const size_t line ) const; 
  std::vector<T>& operator[]( const size_t line ); 
private:
  size_t line;
  size_t column;
  std::vector<std::vector<T>> m_Table;
};

template<typename T>
Table<T>::Table( const size_t l, const size_t c )
    : line {l}
    , column {c}
{
  if( !line || !column ) 
    line = column = 0;
  else
  {
    std::vector<T> vColumn (column);
    for( size_t i = 0; i != line; ++i )
      m_Table.push_back( vColumn );
  }
}

template<typename T>
void Table<T>::Resize( const size_t l, const size_t c )
{
  std::vector<T> vColumn (c);
  if( l > line )
  {
    for( size_t i = 0; i != (l - line); ++i )
      m_Table.push_back( vColumn );
  }
  else
    m_Table.erase(std::next(m_Table.begin(),l), m_Table.end());
  line = l;
  
  if( c > column )
  {
    for( auto& col : m_Table )
      col.insert( col.end(), (c - column), {} );
  }
  else
  {
    for( auto& col : m_Table )
      col.erase(std::next(col.begin(),c), col.end() );
  }
  column = c;
}

template<typename T>
std::pair<size_t, size_t> Table<T>::Size() const
{
  return { line, column };
}

template<typename T>
std::vector<T>& Table<T>::operator[]( const size_t col ) const 
{
  return m_Table.at(col);
}

template<typename T>
std::vector<T>& Table<T>::operator[]( const size_t col ) 
{
  return m_Table.at(col);
}


int main()
{
	return 0;
}
