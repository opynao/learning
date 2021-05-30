#pragma once
#include <iostream>
#include "route_manager.h"

class Parser
{
public:
    Parser(std::istream &is, std::ostream &os);

    void ParseQuery(RouteManager &routes);

private:
    std::istream &m_is;
    std::ostream &m_os;
};