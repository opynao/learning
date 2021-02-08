#pragma once

class Noncopyable
{
public:
  Noncopyable() = default;

  Noncopyable( const int value );
  
//  Noncopyable( int&& value );

  Noncopyable( const Noncopyable& other); 

  Noncopyable& operator=( const Noncopyable& other);

  Noncopyable( Noncopyable&& other);

  Noncopyable& operator=( Noncopyable&& other );

  int GetValue() const;

private:
  int value_ {};
};

bool operator == ( const Noncopyable& lhs, const Noncopyable& rhs );

bool operator < ( const Noncopyable& lhs, const Noncopyable& rhs );
