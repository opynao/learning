#pragma once

#include "route.h"
#include "bus.h"
#include "stop.h"
#include "stops_map.h"
#include "route_description.h"

// класс, который будет хранить в себе все маршруты

class RouteStore
{
public:
    void Add(const Bus &bus, const std::shared_ptr<IRoute> &stops, const RouteDescription routeDescription)
    {
        m_routes[bus] = stops;
    }

    bool Has(const Bus &bus) const
    {
        return m_routes.find(bus) != m_routes.cend();
    }

    size_t GetRouteSizeInStops(const Bus &bus) const
    {
        return m_routes.at(bus)->SizeInStops();
    }
    size_t GetUniqueStops(const Bus &bus) const
    {
        return m_routes.at(bus)->UniqueStops();
    }
    double GetRouteDistance(const Bus &bus) const
    {
        return m_routes.at(bus)->CalculateDistance();
    }

private:
    std::map<Bus, std::shared_ptr<IRoute>> m_routes;
};