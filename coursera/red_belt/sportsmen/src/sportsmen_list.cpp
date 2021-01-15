#include "sportsmen_list.h"
#include <iostream>
#include <algorithm>
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

void SportsmenList::Add( const size_t sportsmen, const size_t next_sportsmen )
{
  it_[sportsmen] = row.insert( it_[next_sportsmen], sportsmen );
}

const SportsmenList::SportsmenRow_t& SportsmenList::Get() const
{
  return row;
}

