#include "parser.h"

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

