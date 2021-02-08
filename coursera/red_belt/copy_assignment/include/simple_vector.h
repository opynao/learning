#pragma once
#include <cstdlib>
#include <algorithm>
#include <iostream>
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

template <typename T>
class SimpleVector 
{
public:
  SimpleVector()
  {}
  
  explicit SimpleVector(size_t size)
  {
    data_ = new T[size];
    end_ = data_ + size;
    counter = size;
  }
  
  ~SimpleVector()
  {
    delete[] data_;
  }

  T& operator[](size_t index)
  {
    return *(data_ + index);
  }

  T* begin()
  {
    return data_;
  }

  T* end()
  {
    return data_ + counter;
  }
  
  const T* begin() const
  {
    return data_;
  }

  const T* end() const
  {
    return data_ + counter;
  }

  size_t Size() const
  {
    return counter;
  }
  
  size_t Capacity() const
  {
    return end_ - data_;
  }
  
  void PushBack(const T& value)
  {
    if( IsEmpty() )
    {
      data_ = new T[1];
      end_ = data_ + 1;
      data_[0] = value;
      counter = 1;
      return;
    }
    if( SizeIsEqualCapacity() )
    {
      size_t newSize = 2 * this->Capacity();
      T* dest = new T[ newSize ];
      std::copy( data_, end_, dest );
      delete[] data_;
      data_ = dest;
      end_ = dest + newSize;
      data_[counter] = value;
      ++counter;
      return;
    }
    data_[counter] = value;
    ++counter;
  }

  SimpleVector<T>& operator=( const SimpleVector<T>& other ) 
  {
    if( this == &other )
      return *this;
   
    if( other.Size() <= Capacity() )
    {
      std::copy( other.begin(), other.end(), begin() );
      counter = other.counter;
    }
    else
    {
      size_t newSize = other.Size();
      T* dest = new T[ newSize ];
      std::copy( other.begin(), other.end(), dest );
      delete[] data_;
      data_ = dest;
      end_ = dest + newSize;
      counter = other.counter;
    }
    return *this;
  }

private:
  bool IsEmpty()
  {
    return !this->Capacity();
  }
  bool SizeIsEqualCapacity()
  {
    return this->Size() == this->Capacity();
  }

private: 
  T* data_ {nullptr};
  T* end_ {nullptr};
  size_t counter {};
};


class MyClass
{
private:
  static int copyNumbers;
public:
  MyClass() 
  {
    std::cout << "Constructor" << std::endl;
    copyNumbers++;
  }
  ~MyClass()
  {
    std::cout << "Destructor" << std::endl;
  }
};

int MyClass::copyNumbers = 0;
