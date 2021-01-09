#pragma once
#include "route_manager.h"
#include <iostream>
#include <string>

class Parser
{
public:
  Parser( std::istream& is, std::ostream& os, RouteManager& routes)
    : m_is {is}
    , m_os {os}
    , m_routes {routes}
  {}
  void Parse();
  void MakeQuery();
private:
  std::istream& m_is;
  std::ostream& m_os;
  RouteManager m_routes;
};

