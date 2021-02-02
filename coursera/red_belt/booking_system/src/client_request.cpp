#include "client_request.h"

ClientRequest::ClientRequest( const HotelName_t& )
{
}

std::optional< size_t > ClientRequest::GetAnswer() const 
{
  return answer_;
}

void ClientRequest::SetAnswer( const size_t answer ) 
{
  answer_ = answer;
}

