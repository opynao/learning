#pragma once
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <map>


#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

template <typename TAirport>
class AirportCounter 
{
private:
  static const auto SIZE { static_cast<size_t>(TAirport::Last_) };

public:
  using Item = std::pair<TAirport, size_t>;
  using Items = std::array< Item, SIZE >;

public:
  AirportCounter()
  {
    for( size_t i = 0; i!= SIZE; ++i )
      items[i].first = static_cast<TAirport>(i);
  }
  
  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end)
    :AirportCounter()
  {
    std::for_each( begin, end, [this] (const TAirport s) { Insert(s); } );
  }
  
  size_t Get(TAirport airport) const { return items[ GetIndex(airport) ].second; }

  void Insert(TAirport airport) { ++GetFlights(airport); }

  void EraseOne(TAirport airport) { --GetFlights(airport); }

  void EraseAll(TAirport airport) { GetFlights(airport) = 0; }

  Items GetItems() const { return items; }

private:
  size_t GetIndex(const TAirport& airport) const 
  { 
    return static_cast<size_t>(airport); 
  }
  
  size_t& GetFlights(const TAirport& airport) 
  { 
    return items[ GetIndex(airport) ].second;
  }

private:
  Items items;
};
