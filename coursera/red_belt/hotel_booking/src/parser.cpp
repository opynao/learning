#include "parser.h"
#include "booking_manager.h"

#include <string>
#include <cstdint>

void Parse( std::istream& is, std::ostream& os )
{
  BookingManager bm;
  
  int numberQueries {};
  is >> numberQueries;
  
  std::string hotelName {};
  int clientId {};
  int roomCount {};
  int64_t time {};
  
  while( numberQueries-- )
  {
    std::string query {};
    is >> query;
    if( query == "BOOK")
    {
      is >> time >> hotelName >> clientId >> roomCount;
      bm.Book( time, hotelName, clientId, roomCount );
    }
    else if( query == "CLIENTS" )
    {
      is >> hotelName;
      os << bm.Clients( hotelName ) << std::endl;
    }
    else
    {
      is >> hotelName;
      os << bm.Rooms( hotelName ) << std::endl;
    }
  }
}
