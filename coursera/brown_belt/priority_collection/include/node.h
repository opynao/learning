#pragma once

#include <iostream>

#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " " <<  __LINE__ << std::endl

template < typename T >
class Node
{
public:
  Node( const T& );

  Node( T&& );

  Node( const Node<T>& );

  Node<T>& operator=( const Node<T>& );

  Node( Node<T>&& );

  Node<T>& operator=( Node<T>&& other );

  void IncreasePriority() const;

  int GetPriority() const;
  
  const T& GetValue() const;

  T Get() const
  {
    return value_;
  }

  bool operator<( const Node<T>& other) const
  {
    if( GetPriority() == other.GetPriority() )
      return insertion_ < other.insertion_;
    return GetPriority() < other.GetPriority();
  }

private:
  T value_;
  mutable int priority_;
  static size_t insertionOrder_;
  size_t insertion_;
};

template < typename T >
size_t Node<T>::insertionOrder_ {};

template < typename T >
Node<T>::Node( const T& value )
  : value_ { value }
  , priority_ {}
{
   insertionOrder_++;
   std::cout << "Copy in construct\n";
}

template < typename T >
Node<T>::Node( T&& value )
  : value_ { std::move( value ) }
  , priority_ {}
{
  insertion_ = ++insertionOrder_;
  std::cout << "Move in construct\n";
}

template < typename T >
Node<T>::Node( const Node<T>& other )
  : value_ { other.value_ }
  , priority_ { other.priority_ }
{
  std::cout << "Copy ctor\n";
}

template < typename T >
Node<T>& Node<T>::operator=( const Node<T>& other )
{
  value_ = other.value_;
  priority_ = other.priority_;
  std::cout << "Copy assign\n";
  return *this;
}

template < typename T >
Node<T>::Node( Node<T>&& other )
  : value_ { std::move( other.value_ ) }
  , priority_ { std::move( other.priority_ ) }
  , insertion_ { std::move( other.insertion_ ) }
{
  std::cout << "Move ctor\n";
}

template < typename T >
Node<T>& Node<T>::operator=( Node<T>&& other )
{
  value_ = std::move( other.value_ );
  priority_ = std::move( other.priority_ );
  std::cout << "Move assign\n"; 
  return *this;
}

template < typename T >
void Node<T>::IncreasePriority() const
{
  ++priority_;
}

template < typename T >
int Node<T>::GetPriority() const
{
  return priority_;
}

template< typename T >
const T& Node<T>::GetValue() const
{
  return value_;
}
