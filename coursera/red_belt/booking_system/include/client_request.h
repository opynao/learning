#pragma once
#include "request.h"

using HotelName_t = std::string;

class ClientRequest : public Request
{
public:
  explicit ClientRequest( const HotelName_t& );
  std::optional< size_t > GetAnswer() const override;
  void SetAnswer( const size_t answer ) override;
private:
  std::optional< size_t > answer_;
};
