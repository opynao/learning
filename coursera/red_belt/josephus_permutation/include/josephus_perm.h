#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) 
{
  list<typename RandomIt::value_type> pool;
  std::move( first, last, pool.begin() );
  size_t cur_pos = 0;
  while ( !pool.empty() ) 
  {
    *(first++) = std::move( std::next( pool.begin(), cur_pos ) );

    pool.erase( std::next( pool.begin(), cur_pos) );
    
    if (pool.empty()) 
      break;
    
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}

struct NoncopyableInt 
{
  int value;

  NoncopyableInt(int value) 
    : value(value) 
  {}

  NoncopyableInt(const NoncopyableInt&) = delete;

  NoncopyableInt& operator=( const NoncopyableInt& ) = delete;

  NoncopyableInt( NoncopyableInt&& ) = default;
  NoncopyableInt& operator=( NoncopyableInt&& ) = default;
};

bool operator == ( const NoncopyableInt& lhs, const NoncopyableInt& rhs ) 
{
  return lhs.value == rhs.value;
}

std::ostream& operator << (std::ostream& os, const NoncopyableInt& v) 
{
  return os << v.value;
}

