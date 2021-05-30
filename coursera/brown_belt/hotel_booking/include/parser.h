#pragma once
#include "booking_manager.h"

#include <iostream>

class Parser
{
public:
    Parser(std::istream &is, std::ostream &os);
    void ParseRequest(BookingManager &);

private:
    std::istream &m_is;
    std::ostream &m_os;
};