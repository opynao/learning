#include "parser.h"

#include <iomanip>

Parser::Parser(std::istream &is, std::ostream &os)
    : m_is{is}, m_os{os}
{
    ReadingManager manager;

    int query_count;
    m_is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
        ParseQuery(manager);
}

void Parser::ParseQuery(ReadingManager &manager)
{
    std::string query_type;
    m_is >> query_type;

    int user_id;
    m_is >> user_id;

    if (query_type == "READ")
    {
        int page_count;
        m_is >> page_count;
        manager.Read(user_id, page_count);
    }

    else if (query_type == "CHEER")
        m_os << std::setprecision(6) << manager.Cheer(user_id) << "\n";
}