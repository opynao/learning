#include "booking_manager.h"

void BookingManager::HandleRequest( const std::unique_ptr<Request>& request)
{
  request->SetAnswer(0); 
}

