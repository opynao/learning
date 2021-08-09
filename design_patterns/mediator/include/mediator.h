#pragma once

#include <string>

class Mediator
{
public:
    virtual ~Mediator() = default;
    virtual void mediate(const std::string &event) = 0;
};
