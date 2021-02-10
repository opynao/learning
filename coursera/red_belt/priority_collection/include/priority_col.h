#pragma once

#include "node.h"

#include <algorithm>
#include <iterator>
#include <set>
#include <utility>

template <typename T>
class PriorityCollection 
{
public:
  using Id = std::<set>::iterator;

public:
  Id Add(T object)
  {
    return prioritySet.insert( std::move( object ) );
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin)
  {
    for( ; range_begin != range_end; ++range_begin )
    {
      ids_begin = prioritySet.insert( *std::make_move_iterator( range_begin ) );
      ++ids_begin;
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const
  {
    return prioritySet.find( *id ) == prioritySet.cend() ? false : true;
  }

  const T& Get(Id id) const
  {
    if( IsValid )
      return *prioritySet.find( *id );
    else
      return;
  }

  void Promote(Id id)
  {
    if( IsValid )
      (*prioritySet.find( *id )).IncreasePriority();
    else
      return;
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const
  {

  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax();

private:
  std::multiset< Priority > prioritySet;// Приватные поля и методы
};

template <typename T>
Id Add(T object)
{
  return prioritySet.insert( std::move( object ) );
}

template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void Add(ObjInputIt range_begin, ObjInputIt range_end,
         IdOutputIt ids_begin)
{
  for( ; range_begin != range_end; ++range_begin )
  {
    ids_begin = prioritySet.insert( *std::make_move_iterator( range_begin ) );
    ++ids_begin;
  }
}

template <typename T>
bool IsValid(Id id) const
{
  return prioritySet.find( *id ) == prioritySet.cend() ? false : true;
}

template <typename T>
const T& Get(Id id) const
{
  if( IsValid )
    return *prioritySet.find( *id );
  else
    return;
}

template <typename T>
void Promote(Id id)
{
    if( IsValid )
      (*prioritySet.find( *id )).IncreasePriority();
    else
      return;
  }

template <typename T>
pair<const T&, int> GetMax() const
{
  if( !prioritySet.empty() )
  {
    auto elem = *std::max_element( std::begin( prioritySet ), std::end( prioritySet ))
    return { elem.GetValue(), elem.GetPriority() };
  }
  else
    return;
}

template <typename T>
pair<T, int> PopMax()
{
/*  if( !prioritySet.empty() )
  {
    auto elem = std::max_element( std::begin( prioritySet ), std::end( prioritySet ));
    return prioritySet.extract( elem )
  }
  else
    return;
    */
  return {};
}


