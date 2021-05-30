#pragma once
#include "domain_validator.h"
#include <iostream>

class Parser
{
public:
    Parser(std::istream &is, std::ostream &os);

private:
    domains_t ParseDomains();

private:
    std::istream &m_is;
    std::ostream &m_os;
};