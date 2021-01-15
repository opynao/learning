#pragma once
#include <algorithm>
#include <numeric>
#include <vector>

template <typename T>
void Swap(T* first, T* second)
{
  T temp = *first;
  *first = *second;
  *second = temp;
};


template <typename T>
void SortPointers(std::vector<T*>& pointers)
{
  std::sort( pointers.begin(), pointers.end(), [] (int* rhs,int* lhs) { return *rhs < *lhs;} );
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination)
{
  T* dest_begin = destination;
  T* dest_end = destination + count;
  T* source_begin = source;
  T* source_end = source + count;
  if (dest_begin >= source_end || dest_end <= source_begin) 
    std::reverse_copy(source_begin, source_end, dest_begin);
  else if (dest_begin > source_begin) 
  {
    /* Случай, когда целевая область лежит правее исходной
     * |   |   |   |d_6|d_5|d_4|d_3|d_2|d_1|
     * |s_1|s_2|s_3|s_4|s_5|s_6|   |   |   |
     * */
    for (size_t i = 0; source_begin + i < dest_begin; ++i) 
      *(dest_end - i - 1) = *(source_begin + i);
    
    std::reverse(dest_begin, source_end);

  } 
  
  else 
  {
    /* Случай, когда целевая область лежит левее исходной
     * |d_6|d_5|d_4|d_3|d_2|d_1|   |   |   |
     * |   |   |   |s_1|s_2|s_3|s_4|s_5|s_6|
     * */
    for (size_t i = 0; source_end - i - 1 >= dest_end; ++i) 
      *(dest_begin + i) = *(source_end - i - 1);
 
    std::reverse(source_begin, dest_end);
  }
}
