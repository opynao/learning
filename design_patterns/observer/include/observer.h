#pragma once

class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void Update(const double temperature, const double humidity, const double pressure) = 0;
};