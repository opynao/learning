#include "client_data.h"

#include <deque>
#include <algorithm>
#include <set>

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
  while( !time_.empty() && *time_.begin() <= ( time - MINUTES_IN_DAY ) )
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
