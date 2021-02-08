#include <iterator>
#include <numeric>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <list>
#include <utility>
#include <iterator>
#include <sstream>

#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

using namespace std;

template <typename RandomIt>
std::list<typename RandomIt::value_type> MoveRangeToPool ( RandomIt first, RandomIt last );

template <typename It>
It FindNextIt( std::list< typename It::value_type >& pool, It it);


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) 
{
  auto pool = MoveRangeToPool( first, last );

  auto it = pool.begin();

  while ( !pool.empty() ) 
  {
    *(first++) = std::move( *(it) ) ;
 
    auto toDelete = it;
    if( pool.size() != 1 )
    {
      for( size_t i = 0; i != step_size; ++i )
      {
        it = FindNextIt( pool, it );
        
        if( it == toDelete)
          it = FindNextIt( pool, it );
      }
    }
 
    if( it == toDelete )
        it = FindNextIt( pool, it );
  
    pool.erase( toDelete );

    if (pool.empty()) 
     break;
  }
}

template <typename It>
It FindNextIt( std::list< typename It::value_type >& pool, It it)
{
  if( std::next(it) != pool.end() )
    it++;
  else
    it = pool.begin();
  return it;
}

template <typename RandomIt>
std::list<typename RandomIt::value_type> MoveRangeToPool ( RandomIt first, RandomIt last )
{
  std::list<typename RandomIt::value_type> pool;
  std::move( first, last, std::inserter( pool, pool.end() ) );
  return pool;
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

int main()
{
  return 0;
}
