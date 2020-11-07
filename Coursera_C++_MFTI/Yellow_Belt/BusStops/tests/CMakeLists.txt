cmake_minimum_required(VERSION 3.10)

project(TestingBusStops)

add_executable(testBusStops BusStopsTests.cpp)
target_link_libraries(testBusStops busStops_lib)
add_test(NAME testBusStops COMMAND testBusStops)


