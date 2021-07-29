#include "gtest/gtest.h"
#include "stop.h"
#include "stops_map.h"

#include <memory>

TEST(StopsMap, AfterCreation_StopsMapIsEmpty)
{
    StopsMap stopsMap;
    EXPECT_EQ(stopsMap.IsEmpty(), true);
}

TEST(StopsMap, SizeOfEmptyStopsMap_IsNull)
{
    StopsMap stopsMap;
    EXPECT_EQ(stopsMap.Size(), 0);
}

TEST(StopsMap, AddNewStop_NewStopAdded)
{
    Stop stop;
    Coordinate coordinate;
    StopsMap stopsMap;
    const size_t storeSizeBeforeNewStopAdded{stopsMap.Size()};
    stopsMap.Add(stop, coordinate);
    EXPECT_EQ(stopsMap.Size(), storeSizeBeforeNewStopAdded + 1);
}

TEST(StopsMap, HasStoredStop_HasStop)
{
    Stop stop;
    Coordinate coordinate;
    StopsMap stopsMap;
    stopsMap.Add(stop, coordinate);
    EXPECT_EQ(stopsMap.Has(stop), true);
}