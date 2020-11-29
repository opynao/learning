#include "parse_date_event.h"


std::string ParseEvent(std::istream& is) 
{
  std::string event;
  is >> std::ws;
  std::getline(is, event);
  return event;
}


