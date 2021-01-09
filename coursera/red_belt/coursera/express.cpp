#include <map>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

class RouteManager 
{
public:
  void AddRoute(int start, int finish);
  int FindNearestFinish(int start, int finish) const; 
private:
  std::map<int, std::set<int>> reachable_lists_;
};

class Parser
{
public:
  Parser( std::istream& is, std::ostream& os, RouteManager& routes)
    : m_is {is}
    , m_os {os}
    , m_routes {routes}
  {}
  void Parse();
  void MakeQuery();
private:
  std::istream& m_is;
  std::ostream& m_os;
  RouteManager m_routes;
};

void Parser::Parse()
{
  size_t query_count;
  m_is >> query_count;
  while( query_count-- )
    MakeQuery();
}

void Parser::MakeQuery()
{
    std::string query_type;
    m_is >> query_type;
    int start, finish;
    m_is >> start >> finish;
    if (query_type == "ADD") 
      m_routes.AddRoute(start, finish);
    else if (query_type == "GO") 
      m_os << m_routes.FindNearestFinish(start, finish) << "\n";
}

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

int main() 
{
  RouteManager routes;
  Parser pr( std::cin, std::cout, routes );
  pr.Parse();
  return 0;
}
