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
    : first_ (f)
    , last_ (l)
  {}

  iterator begin() { return first_; }
  iterator end() { return last_; }
  const_iterator begin() const { return first_; }
  const_iterator end() const { return last_; }

  size_t size() const { return std::distance(first_, last_); }

private:
  Iterator first_;
  Iterator last_;
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
 
public:
 Paginator( Iterator begin, Iterator end, size_t pageSize )
 {
    for ( size_t left = std::distance(begin, end); left > 0; ) 
    {
      size_t current_page_size = std::min( pageSize, left );
      Iterator current_page_end = std::next( begin, current_page_size );
      pages_.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
 }
 
 auto begin()  { return pages_.begin(); }
 auto end() { return pages_.end(); }
 
 size_t size() const { return pages_.size(); }
 
 private:
  Page_t pages_;
};

template <typename C>
auto Paginate(C& c, size_t page_size) 
{
  return Paginator( std::begin(c), std::end(c), page_size ); 
}

