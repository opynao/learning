#pragma once
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <iostream>
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

template <typename T>
class SimpleVector 
{
public:
  SimpleVector() = default;
  
  explicit SimpleVector(size_t size) { AllocateMemory( size ); }
  
  ~SimpleVector()                    { delete[] data_; }

  T& operator[]( size_t index )      { return *(data_ + index); }

  T* begin()                         { return data_; }

  T* end()                           { return data_ + counter; }

  size_t Size() const                { return counter; }
   
  size_t Capacity() const            { return end_ - data_; }
  
  void PushBack(const T& value)
  {
    if( IsEmpty() )
    {
      AllocateMemory( 1 );
      data_[0] = std::move(const_cast<T&>(value));
      return;
    }
    if( SizeIsEqualCapacity() )
    {
      size_t newSize = 2 * Capacity();
      T* dest = new T[ newSize ];
      std::move( data_, end_, dest );
      delete[] data_;
      
      data_ = dest;
      end_ = dest + newSize;
      data_[counter] = std::move( const_cast<T&>(value));
      ++counter;
      
      return;
    }
    data_[counter] = std::move(const_cast<T&>(value));
    ++counter;
  }

private:
  
  bool IsEmpty() { return !Capacity(); }
  
  bool SizeIsEqualCapacity() { return Size() == Capacity(); }
  
  void AllocateMemory( const size_t size )
  {
    data_ = new T[size];
    end_ = data_ + size;
    counter = size;
  }

private: 
  T* data_ {nullptr};
  T* end_ {nullptr};
  size_t counter {};
};
