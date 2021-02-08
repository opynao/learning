#include "non_copy.h"
#include <iostream>

Noncopyable::Noncopyable( const int value )
  : value_( value )
{
  std::cout << "copy in construct\n";
}
/*
Noncopyable::Noncopyable( int&& value )
  : value_( std::move(value) )
{
   std::cout << "move in construct\n";
}
*/
Noncopyable::Noncopyable( const Noncopyable& other) 
  : value_ { other.value_ }
{
  std::cout << "Copy ctor\n";
}

Noncopyable& Noncopyable::operator=( const Noncopyable& other)
{
 value_ = other.value_;
 std::cout << "Copy assign\n";
 return *this;
}

Noncopyable::Noncopyable( Noncopyable&& other)
  : value_ { std::move( other.value_ ) }
{
  std::cout << "Move ctor\n";
}

Noncopyable& Noncopyable::operator=( Noncopyable&& other )
{
  value_ = std::move( other.value_ );
  std::cout << "Move assign\n"; 
  return *this;
}

int Noncopyable::GetValue() const
{
  return value_;
}

bool operator == ( const Noncopyable& lhs, const Noncopyable& rhs )
{
  return lhs.GetValue() == rhs.GetValue();
}

bool operator < ( const Noncopyable& lhs, const Noncopyable& rhs )
{
  return lhs.GetValue() < rhs.GetValue();
}
