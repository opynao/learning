#pragma once
#include "i_command.h"

class IInputControllerEvents
{
public:
    virtual ~IInputControllerEvents() = default;
    virtual void OnStopAddCommand(const StopAddCommand &) = 0;
    virtual void OnRouteAddCommand(const RouteAddCommand &) = 0;
    virtual void OnInfoGetCommand(const InfoGetCommand &) = 0;
};