#pragma once
#include "stop.h"

#include <vector>

class IRoute
{
public:
    void AddStop(const Stop &stop)
    {
        m_stopsOnRoute.push_back(stop);
    }
    virtual size_t SizeInStops() const = 0;
    virtual size_t UniqueStops() const = 0;
    virtual double CalculateDistance() const = 0;

protected:
    std::shared_ptr<StopsMap> m_spStopsMap;
    std::vector<Stop> m_stopsOnRoute;
};

class CircularRoute : public IRoute
{
public:
    size_t SizeInStops() const override
    {
        return m_stopsOnRoute.size();
    }
    size_t UniqueStops() const override
    {
        return m_stopsOnRoute.size() - 1;
    }
    double CalculateDistance() const override
    {
    }
};

class StraightRoute : public IRoute
{
public:
    size_t SizeInStops() const override
    {
        return m_stopsOnRoute.size() * 2 - 1;
    }
    size_t UniqueStops() const override
    {
        return m_stopsOnRoute.size();
    }
    double CalculateDistance() const override
    {
    }
};