#pragma once

#include <cstddef>

class RouteInfo
{
public:
    RouteInfo(const size_t stopsOnRoute, const size_t uniqueStops, const double routeLength)
        : m_stopsOnRoute{stopsOnRoute}, m_uniqueStops{uniqueStops}, m_routeLength{routeLength}
    {
    }

    size_t GetStopsOnRoute() const
    {
        return m_stopsOnRoute;
    }
    size_t GetUniqueStops() const
    {
        return m_uniqueStops;
    }
    double GetRouteLength() const
    {
        return m_routeLength;
    }

private:
    size_t m_stopsOnRoute;
    size_t m_uniqueStops;
    double m_routeLength;
};