#pragma once

#include "hotel_data.h"

#include <cstdint>
#include <string>
#include <map>

class BookingManager
{
public:
  using hotelName_t = std::string;
  using time_t = int64_t;
  using client_t = int;
  using roomCount_t = int;

public:
  void Book( const time_t , const hotelName_t&, const client_t, const roomCount_t );

  int Clients( const hotelName_t& );
  
  int Rooms( const hotelName_t& );

  size_t GetStorageSize() const;

private:
  time_t current_time_;
  std::map< hotelName_t, HotelData > storage;
};
