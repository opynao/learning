#pragma once

#include "i_observer.h"
#include "i_event.h"
#include "bus.h"
#include "route_store.h"
#include "route_info.h"

#include <memory>
#include <optional>

// внешний интерфейс, посредством которого будет проихсодить общение между I/O и БД
// c  InputController'ом связан посредством паттерна Издатель-Подписчик
// (то есть подписывается на события, приходящие в инпуте)

class TransportDirectoryApi : public IInputControllerEvents
{
public:
    void OnStopAddCommand(const StopAddCommand &stopAddCommand)
    {
        AddStop(stopAddCommand.GetStop(), stopAddCommand.GetCoordinate());
    }
    void OnRouteAddCommand(const RouteAddCommand &routeAddCommand)
    {
        AddRoute(routeAddCommand.GetBusNumber(), routeAddCommand.GetBusRoute());
    }
    std::optional<RouteInfo> OnInfoGetCommand(const InfoGetCommand &)
    {
        return GetRouteInfo(InfoGetCommand.GetBusNumber());
    }

private:
    void AddStop(const Stop &stop, const Coordinate &coordinate)
    {
        stopsMap.Add(stop, coordinate);
    }
    void AddRoute(const Bus &bus, const std::shared_ptr<IRoute> &route)
    {
        routeStore.Add(bus, route);
    }
    std::optional<RouteInfo> GetRouteInfo(const Bus &bus)
    {
        if (routeStore.Has(bus))
            return RouteInfo{routeStore.GetRouteSizeInStops(bus), routeStore.GetUniqueStops(bus), routeStore.GetRouteDistance(bus)};
        return std::nullopt;
    }

private:
    StopsMap stopsMap;
    RouteStore routeStore;
};