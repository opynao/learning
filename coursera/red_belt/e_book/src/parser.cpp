#include "parser.h"
#include <iomanip>

using namespace std;
#ifdef ETALON
void Parser::Parse()
{
  int query_count;
  m_is >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    m_is >> query_type;
    int user_id;
    m_is >> user_id;

    if (query_type == "READ") {
      int page_count;
      m_is >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") 
    {
      m_os << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }
}
#endif

#ifndef ETALON
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
    int user_id;
    m_is >> user_id;
    
    auto it_query = m.find(query_type);
    
    switch( it_query->second )
    {
      case QueryType::READ:
        int page_count;
        m_is >> page_count;
        m_rm.Read(user_id, page_count);
        break;

      case QueryType::CHEER:
        m_os << std::setprecision(6) << m_rm.Cheer(user_id) << "\n";
        break;
    }
}
#endif
