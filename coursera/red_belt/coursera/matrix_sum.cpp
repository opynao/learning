#include <iterator>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <future>

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
	using T = decltype(std::begin(c));
  return Paginator<T>( std::begin(c), std::end(c), page_size ); 
}

template <typename ContainerOfVectors>
int64_t SumSingleThread( const ContainerOfVectors& matrix ) 
{
  int64_t sum = 0;
  for (const auto& row : matrix) 
  {
    for (auto item : row) 
      sum += item;
  }
  return sum;
}

int64_t CalculateMatrixSum(const std::vector< std::vector<int>>& matrix) 
{
  int64_t result {};
  std::vector< std::future<int64_t>> futures {};
  
  for( auto& page : Paginate( matrix, 2000 ))
     futures.push_back( std::async( [=] { return SumSingleThread(page); } ));
  
  for( auto& f : futures )
    result += f.get();  

  return result;
}

int main()
{
	return 0;
}
