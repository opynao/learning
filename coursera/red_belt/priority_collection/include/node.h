#pragma once

#include <iostream>

template < typename T >
class Node
{
  Node( T&& );
 
  Node( const Node& );

  Node& operator=( const Node& );

  Node( Node&& );

  Node& operator=( Node&& other );

  void IncreasePriority();

  int GetPriority() const;
  
  T GetValue() const;

private:
  T value_;
  int priority_;

};

template < typename T >
bool operator<( Node<T>& lhs, Node<T>& rhs )
{
  return lhs.GetPriority() < rhs.GetPriority();
}

template < typename T >
Node( T&& value )
  : value_ { std::move( value ) }
  , priority_ {}
{
   std::cout << "Move int\n";
}

template < typename T >
Node( const Node& other )
  : value_ { other.value_ }
  , priority_ { other.priority_ }
{
  std::cout << "Copy ctor\n";
}

template < typename T >
Node& operator=( const Node& other )
{
  value_ = other.value_;
  priority_ = other.priority_;
  std::cout << "Copy assign\n";
  return *this;
}

template < typename T >
Node( Node&& other )
  : value_ { std::move( other.value_ ) }
  , priority_ { std::move( other.priority_ ) }
{
  std::cout << "Move ctor\n";
  ++countMoveCtor;
}

template < typename T >
Node& operator=( Node&& other )
{
  value_ = std::move( other.value_ );
  priority_ = std::move( other.priority_ );
  std::cout << "Move assign\n"; 
  return *this;
}

template < typename T >
void IncreasePriority()
{
  ++priority_;
}

template < typename T >
int GetPriority() const
{
  return priority;
}

template< typename T >
T GetValue() const
{
  return value_;
}
