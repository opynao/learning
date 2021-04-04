#include <future>

#include "generate.h"

std::vector< std::vector< int >> GenerateMatrix( size_t size )
{
  std::vector< std::vector<int >> result( size );
  for( auto& row : result ) 
  {
    row.reserve( size );
    for(size_t column = 0; column < size; ++column) 
      row.push_back(1);
  }
  return result;
}
