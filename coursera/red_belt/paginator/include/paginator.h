#pragma once

#include <iterator>
#include <vector>
#include <iostream>
#include <cmath>

template <typename Iterator>
class IteratorRange 
{
public:
  using iterator = Iterator;
  using const_iterator = const Iterator;
public:
  IteratorRange(Iterator f, Iterator l)
    : first (f)
    , last (l)
  {}
  iterator begin() { return first; }
  iterator end() { return last; }
  const_iterator begin() const { return first; }
  const_iterator end() const { return last; }

  size_t size() const { return std::distance(first, last); }

private:
  Iterator first;
  Iterator last;
};

template<typename Iterator>
IteratorRange<Iterator> MakeRange (Iterator begin, Iterator end) 
{
  return IteratorRange<Iterator>(begin, end);
}


template <typename Iterator>
class Paginator 
{
public:
 using Page_t = std::vector<IteratorRange<Iterator>>;
 using iterator = typename Page_t::iterator;
 using const_iterator = typename Page_t::const_iterator;
 
public:
 Paginator( Iterator begin, Iterator end, size_t pageSize )
  : m_begin { begin }
  , m_end { end }
  , m_pageSize { pageSize }
  {
    MakePages();
  }

 iterator begin()  { return m_pages.begin(); }
 iterator end() { return m_pages.end(); }
 
 const_iterator begin() const { return m_pages.cbegin(); }
 const_iterator end() const { return m_pages.cend(); }
 
 size_t size() const { return m_pages.size(); }
 
 void MakePages()
 {
    size_t size = std::distance( m_begin, m_end );
    size_t numberOfPages =  size / m_pageSize ;
    if (size % m_pageSize)
      numberOfPages++;

    auto start = m_begin;
    for( size_t i = 0; i != numberOfPages; ++i )
    {
     if( i < numberOfPages - 1)
     {
       IteratorRange<Iterator> it (start, std::next(start, m_pageSize));
       m_pages.push_back(it);
     }
     else
     {
       IteratorRange<Iterator> it (start, m_end);
       m_pages.push_back(it);
     }
     start = std::next(start, m_pageSize);
    }
 }

private:
  Page_t m_pages;
  Iterator m_begin;
  Iterator m_end;
  size_t m_pageSize;
};

template <typename C>
auto Paginate(C& c, size_t page_size) 
{
  using T = decltype(std::begin(c));
  return Paginator<T>( std::begin(c), std::end(c), page_size ); 
}

