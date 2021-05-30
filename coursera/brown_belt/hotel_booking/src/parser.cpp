#include "parser.h"

#include <string>
#include <cstdint>

Parser::Parser(std::istream &m_is, std::ostream &m_os)
    : m_is{m_is}, m_os{m_os}
{
    BookingManager manager;

    int numberQueries{};
    m_is >> numberQueries;

    while (numberQueries--)
        ParseRequest(manager);
}

void Parser::ParseRequest(BookingManager &manager)
{
    std::string hotelName{};
    int clientId{};
    int roomCount{};
    int64_t time{};

    std::string query{};
    m_is >> query;
    if (query == "BOOK")
    {
        m_is >> time >> hotelName >> clientId >> roomCount;
        manager.Book(time, hotelName, clientId, roomCount);
    }
    else if (query == "CLIENTS")
    {
        m_is >> hotelName;
        m_os << manager.Clients(hotelName) << std::endl;
    }
    else
    {
        m_is >> hotelName;
        m_os << manager.Rooms(hotelName) << std::endl;
    }
}