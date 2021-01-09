#include "route_manager.h"
#include <algorithm>
#include <cmath>

void RouteManager::AddRoute(int start, int finish) 
{
  reachable_lists_[start].insert(finish);
  reachable_lists_[finish].insert(start);
}

int RouteManager::FindNearestFinish(int start, int finish) const
{
  int result = std::abs(start - finish);
  if (!reachable_lists_.count(start)) 
      return result;
  
  const std::set<int>& reachable_stations = reachable_lists_.at(start);
  if( reachable_stations.count(finish) )
    return 0;

  auto it = reachable_stations.lower_bound(finish);
  if ( it == reachable_stations.end() )
    return (std::min( result, std::abs(*std::prev(it) - finish)));
  return std::min( {result, std::abs(finish - *it), std::abs(finish - *std::prev(it))});
}
