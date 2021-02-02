#pragma once
#include "request.h"
#include <memory>

class BookingManager
{
public:
  void HandleRequest( const std::unique_ptr<Request>& );
};
