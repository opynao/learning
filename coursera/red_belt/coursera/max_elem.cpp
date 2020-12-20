#include <algorithm>
#include <vector>

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) 
{
  std::vector< typename ForwardIterator::value_type > matches {};
  std::copy_if( first, last, std::back_inserter( matches ), pred );
  if ( matches.empty() )
    return last;
  auto it = std::max_element( matches.cbegin(), matches.cend() );
  return std::find( first, last, *it);
}

int main()
{
  return 0;
}
