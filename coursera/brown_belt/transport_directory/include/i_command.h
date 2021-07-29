#pragma once

#include "stop.h"
#include "coordinate.h"
#include "bus.h"
#include "route.h"

class ICommand
{
public:
    virtual ~ICommand() = default;
};

class StopAddCommand : public ICommand
{
public:
    StopAddCommand(const Stop &stop, const Coordinate &coordinate)
        : m_stop{stop}, m_coordinate{coordinate}
    {
    }
    Stop GetStop() const
    {
        return m_stop;
    }
    Coordinate GetCoordinate() const
    {
        return m_coordinate;
    }

private:
    Stop m_stop;
    Coordinate m_coordinate;
};

class RouteAddCommand : public ICommand
{
public:
    RouteAddCommand(const Bus &bus, const std::shared_ptr<IRoute> spRoute)
    {
    }

private:
    Bus m_bus;
    std::shared_ptr<IRoute> m_spRoute;
};

class InfoGetCommand
{
};
