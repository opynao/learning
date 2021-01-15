#pragma once

#include <stdexcept>
#include <array>
#include <iostream>
#define LOGF std::cerr << __FUNCTION__ << __LINE__ << std::endl

template <typename T, size_t N>
class StackVector 
{
public:
  explicit StackVector(size_t a_size = 0);

  size_t Size() const { return vectorSize_; }
  size_t Capacity() const { return N; }

  T& operator[](size_t index) { return stackVector_[index]; }
  const T& operator[](size_t index) const { return stackVector_[index]; }

  using iterator = typename std::array< T,N >:: iterator;
  using const_iterator = typename std::array< T,N >:: const_iterator;
  iterator begin() { return stackVector_.begin(); }
  iterator end() 
  { 
    if( !Size() ) 
      return stackVector_.begin(); 
    return stackVector_.end(); 
  }
  const_iterator begin() const { return stackVector_.cbegin(); }
  const_iterator  end() const 
  {
    if( !Size() )
      return stackVector_.cbegin();
    return stackVector_.cend(); 
  }
  void PushBack(const T& value);
  T PopBack();

private:
  std::array< T,N > stackVector_;
  size_t vectorSize_ {};
};

template <typename T, size_t N>
StackVector< T,N >::StackVector(size_t a_size)
{
  if( a_size > N )
    throw std::invalid_argument("Size is more than capacity");
  vectorSize_ = a_size;
}

template <typename T, size_t N>
void StackVector< T,N >::PushBack(const T& value)
{
  if( Size() ==  Capacity() )
    throw std::overflow_error("Capacity limit");
  stackVector_[vectorSize_] = value;
  ++vectorSize_;
}

template <typename T, size_t N>
T StackVector< T,N >::PopBack()
{
  if( !vectorSize_ ) 
    throw std::underflow_error("No elements in vector");
  --vectorSize_;
  return stackVector_[vectorSize_];
}


