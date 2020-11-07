cmake_minimum_required(VERSION 3.10)

project(BusStops)

add_executable(busStops main.cpp)

add_library(busStops_lib starter.cpp)
target_link_libraries(busStops busStops_lib)

target_include_directories(busStops PUBLIC /home/vika/projects/pub/src/utils/include/ )

enable_testing()

add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
