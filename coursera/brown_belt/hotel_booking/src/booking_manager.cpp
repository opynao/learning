#include "booking_manager.h"

void BookingManager::Book( const time_t time, const hotelName_t& hotelName, 
                           const client_t clientId, const int roomCount )
{
  storage[ hotelName ].Update( time, clientId, roomCount);
  current_time_ = time;
}

int BookingManager::Clients( const hotelName_t& hotelName ) 
{
  auto it = storage.find( hotelName );
  if( it == storage.cend() )
    return 0;
  return it->second.GetClients( current_time_ );
}

int BookingManager::Rooms( const hotelName_t& hotelName ) 
{
  auto it = storage.find( hotelName );
  if( it == storage.cend() )
    return 0;
  return it->second.GetRooms( current_time_ );
}

size_t BookingManager::GetStorageSize() const
{
  return storage.size();
}

