#pragma once
#include <iostream>

class IDisplay
{
public:
    virtual ~IDisplay() = default;
    virtual void Display(std::ostream &) const = 0;
};