#include "parser.h"

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
