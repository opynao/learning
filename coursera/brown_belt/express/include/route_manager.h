#pragma once
#include <map>
#include <set>

class RouteManager
{
public:
    void AddRoute(const int start, const int finish);

    int FindNearestFinish(const int start, const int finish) const;

private:
    std::map<int, std::set<int>> reachable_lists_;
};
