#pragma once
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
  const std::vector<T>& operator[]( const size_t line ) const; 
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
    Resize( line, column );
}

template<typename T>
void Table<T>::Resize( const size_t l, const size_t c )
{
  line = l;
  column = c;
  m_Table.resize(l);
  for( auto& item : m_Table )
    item.resize(c);
}

template<typename T>
std::pair<size_t, size_t> Table<T>::Size() const
{
  return { line, column };
}

template<typename T>
const std::vector<T>& Table<T>::operator[]( const size_t col ) const 
{
  return m_Table[col];
}

template<typename T>
std::vector<T>& Table<T>::operator[]( const size_t col ) 
{
  return m_Table[col];
}

