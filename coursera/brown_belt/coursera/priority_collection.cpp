#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <utility>
#include <map>

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
}

template < typename T >
Node<T>::Node( T&& value )
  : value_ { std::move( value ) }
  , priority_ {}
{
  insertion_ = ++insertionOrder_;
}

template < typename T >
Node<T>::Node( const Node<T>& other )
  : value_ { other.value_ }
  , priority_ { other.priority_ }
{
}

template < typename T >
Node<T>& Node<T>::operator=( const Node<T>& other )
{
  value_ = other.value_;
  priority_ = other.priority_;
  return *this;
}

template < typename T >
Node<T>::Node( Node<T>&& other )
  : value_ { std::move( other.value_ ) }
  , priority_ { std::move( other.priority_ ) }
  , insertion_ { std::move( other.insertion_ ) }
{
}

template < typename T >
Node<T>& Node<T>::operator=( Node<T>&& other )
{
  value_ = std::move( other.value_ );
  priority_ = std::move( other.priority_ );
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


template <typename T>
class PriorityCollection 
{
public:
  using Id = typename std::multiset< Node<T>>::const_pointer;
  using It = typename std::multiset< Node<T>>::iterator;

public:
  Id Add(T object) 
  { 
     It itInsert = prioritySet.insert( std::move( object ) );
     Id idInsert = &(*itInsert);
     idToIt[ idInsert ] = itInsert;
     return idInsert;
  }
 
  bool IsValid(Id id) const 
  { 
    return idToIt.find( id ) != idToIt.cend();  
  }
  
  void Promote(Id id) 
  {
    auto nh = prioritySet.extract( idToIt[id] );
    nh.value().IncreasePriority();
    It itInsert = prioritySet.insert( std::move( nh.value() ) );
    idToIt[id] = itInsert;
  }

  const T& Get(Id id) const 
  { 
    return (*id).GetValue(); 
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin)
  {
    for( ; range_begin != range_end; ++range_begin )
      *(ids_begin++) = Add( std::move( *range_begin ) );
  }

  std::pair<const T&, int> GetMax() const
  {
    auto itMax = std::prev( prioritySet.cend() );
    return { itMax->GetValue() , itMax->GetPriority() };
  }
  
  std::pair<T, int> PopMax()
  {
    auto itMax = std::prev( prioritySet.cend() );
    auto nh = prioritySet.extract( itMax );
    idToIt.erase( &(*itMax) );
    return { std::move( const_cast<T&>(nh.value().GetValue() ) ), std::move( nh.value().GetPriority() ) };
  }

private:
  std::map< Id, It > idToIt;
  std::multiset< Node<T> > prioritySet;
};

int main() 
{
  return 0;
}
