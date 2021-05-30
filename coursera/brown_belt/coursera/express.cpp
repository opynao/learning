#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <cmath>

class RouteManager
{
public:
    void AddRoute(const int start, const int finish);

    int FindNearestFinish(const int start, const int finish) const;

private:
    std::map<int, std::set<int>> reachable_lists_;
};

class Parser
{
public:
    Parser(std::istream &is, std::ostream &os);

    void ParseQuery(RouteManager &routes);

private:
    std::istream &m_is;
    std::ostream &m_os;
};

Parser::Parser(std::istream &is, std::ostream &os)
    : m_is{is}, m_os{os}
{
    RouteManager routes;

    int query_count;
    m_is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
        ParseQuery(routes);
}
void Parser::ParseQuery(RouteManager &routes)
{
    std::string query_type;
    m_is >> query_type;
    int start, finish;
    m_is >> start >> finish;
    if (query_type == "ADD")
        routes.AddRoute(start, finish);

    else if (query_type == "GO")
        m_os << routes.FindNearestFinish(start, finish) << "\n";
}

void RouteManager::AddRoute(const int start, const int finish)
{
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
}

int RouteManager::FindNearestFinish(const int start, const int finish) const
{
    int result = abs(start - finish);
    if (!reachable_lists_.count(start))
        return result;

    const std::set<int> &reachable_stations = reachable_lists_.at(start);
    if (reachable_stations.count(finish))
        return 0;

    auto it = reachable_stations.lower_bound(finish);
    if (it == reachable_stations.end())
        return (std::min(result, std::abs(*std::prev(it) - finish)));
    return std::min({result, std::abs(finish - *it), std::abs(finish - *std::prev(it))});
}

int main()
{
    Parser(std::cin, std::cout);
    return 0;
}