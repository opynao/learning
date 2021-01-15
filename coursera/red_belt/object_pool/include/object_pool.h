#pragma once
#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <set>
#define LOGF std::cerr<< __FUNCTION__ << ":"<<__LINE__<<std::endl

template <class T>
class ObjectPool 
{
public:
  T* Allocate()
  {
    auto obj =  TryAllocate();
    
    if( obj == nullptr )
       obj = CreateObj();
    return obj;
  }

  T* TryAllocate()
  {
    if( !IsReleased() )
      return nullptr;
    return MoveToAllocated();
  }

  void Deallocate(T* object)
  {    
    const auto it = pointersToAllocatedObjects_.find( object );
    if ( it == pointersToAllocatedObjects_.cend() )
      throw std::invalid_argument("");
    
    pointersToReleasedObjects_.push( *it );
    pointersToAllocatedObjects_.erase( it );
  }

  ~ObjectPool()
  {
    for( auto& item : pointersToAllocatedObjects_ )
      delete item;
   
    while( !pointersToReleasedObjects_.empty() )
    { 
      delete pointersToReleasedObjects_.front();
      pointersToReleasedObjects_.pop();
    }
  }

private:
  bool IsReleased() const
  {
    return !pointersToReleasedObjects_.empty();
  }

 T* CreateObj()
 {    
   return *(pointersToAllocatedObjects_.emplace( new T ).first);
 }

  T* MoveToAllocated()
  { 
    const auto& obj = pointersToReleasedObjects_.front();
    const auto it = pointersToAllocatedObjects_.insert(obj);
    pointersToReleasedObjects_.pop();
    return *(it.first);
  }

private:
  std::set<T*> pointersToAllocatedObjects_ {};
  std::queue<T*> pointersToReleasedObjects_ {};
};

