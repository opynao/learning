#pragma once

#include "node.h"

#include <algorithm>
#include <iterator>
#include <set>
#include <utility>
#include <map>

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
