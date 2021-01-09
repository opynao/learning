#pragma once
#include <map>
#include <set>

class RouteManager 
{
public:
  void AddRoute(int start, int finish);
  int FindNearestFinish(int start, int finish) const; 
private:
  std::map<int, std::set<int>> reachable_lists_;
};



