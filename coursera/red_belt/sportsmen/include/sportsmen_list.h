#pragma once
#include <list>
#include <deque>
#include <vector>
#include <cassert>

class SportsmenList
{
public:
  using SportsmenRow_t = std::list< size_t >;

public:
  SportsmenList()
    : it_( MAX_ATHLETES + 1, row.end() )
  {}
  void Add( const size_t sportsmen, const size_t next_sportsmen );
  const SportsmenRow_t& Get() const;

private:
  static const size_t MAX_ATHLETES {100'000};
  SportsmenRow_t row;
  std::vector< SportsmenRow_t::iterator > it_;
};
