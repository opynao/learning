#include "calculate.h"
#include "paginator.h"

#include <numeric>
#include <future>


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
