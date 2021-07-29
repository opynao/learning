#include "gtest/gtest.h"
#include "stop.h"
#include "route_store.h"
#include "stops_map.h"

#include <memory>

TEST(RouteStore, ConstructWithNullPtr_)
{
}

TEST(RouteStore, AddStop_StopIsInStopsMap)
{
    auto stopsMap = std::make_shared<StopsMap>();
    RouteStore routeStore(stopsMap);
    Stop stop;
    Coordinate coordinate;
    routeStore.AddStop(stop, coordinate);
    EXPECT_EQ(stopsMap.Has(stop), true);
}
