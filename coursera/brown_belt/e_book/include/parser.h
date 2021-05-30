#pragma once
#include <iostream>
#include <string>
#include "reading_manager.h"

class Parser
{
public:
    Parser(std::istream &is, std::ostream &os);

private:
    void ParseQuery(ReadingManager &manager);
    std::istream &m_is;
    std::ostream &m_os;
};