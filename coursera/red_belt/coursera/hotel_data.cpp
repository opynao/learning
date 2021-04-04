#include <cstdint>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <sstream>

const int SECONDS_IN_DAY = 86400;

class ClientData
{
public:  
  using time_t = int64_t;
  using client_t = int;

public:
  void Pop();

  void Push( time_t time, client_t clientId );

  int GetClientsSize( time_t time );

private:
  std::deque< time_t > time_;
  std::deque< client_t > clientId_;
  std::multiset< client_t > clients_;
};

void ClientData::Pop()
{
  if( !time_.empty() )
    time_.pop_front();
  if( !clientId_.empty() )
  {
    clients_.erase( clients_.find( clientId_.front() ));
    clientId_.pop_front();
  }
}

void ClientData::Push( time_t time, client_t clientId )
{
  time_.push_back( time );
  clientId_.push_back( clientId );
  clients_.insert( clientId );
}

int ClientData::GetClientsSize( time_t time )
{
  while( !time_.empty() && *time_.begin() <= ( time - SECONDS_IN_DAY ) )
    Pop();
  
  auto it = clients_.begin();
  size_t count {};
  while( it != clients_.end() )
  {
    it = clients_.upper_bound( *it );
    ++count;
  }
  return count;
}


class HotelData
{
public:
  using time_t = int64_t;
  using client_t = int;
  using roomCount_t = int;

public:
  void Update( time_t, client_t , roomCount_t );

  int GetClients( time_t );

  int GetRooms( time_t );

private:
  std::deque< std::pair<time_t, roomCount_t >> time_roomCount_;
  ClientData clientData_;
  roomCount_t roomCount_;
};

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
         ( time - SECONDS_IN_DAY ) )
  {
    roomCount_ -= (*time_roomCount_.begin()).second;
    time_roomCount_.pop_front();
  }
  return roomCount_;
}
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

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	Parse(std::cin, std::cout);
	return 0;
}
