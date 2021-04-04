#pragma once

#include <vector>
#include <cstdint>

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

int64_t CalculateMatrixSum( const std::vector< std::vector<int>>& );
