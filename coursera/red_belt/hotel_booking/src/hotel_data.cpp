#include "hotel_data.h"

#include <numeric>
#include <algorithm>
#include <iostream>

#define PR(x) std::cerr<< #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " : " << __LINE__ << std::endl

void HotelData::Update( time_t time, client_t clientId, roomCount_t roomCount )
{
  time_roomCount_.push_back( {time, roomCount} );
  roomCount_ += roomCount;
  clientData_.Push( time, clientId );
}

int HotelData::GetClients( time_t time )
{
  return clientData_.GetClientsSize( time );
}

int HotelData::GetRooms( time_t time )
{
  while( !time_roomCount_.empty() && 
         (*time_roomCount_.begin()).first <= 
         ( time - MINUTES_IN_DAY ) )
  {
    roomCount_ -= (*time_roomCount_.begin()).second;
    time_roomCount_.pop_front();
  }
  return roomCount_;
}
