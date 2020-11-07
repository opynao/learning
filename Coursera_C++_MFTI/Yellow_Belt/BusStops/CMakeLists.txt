cmake_minimum_required(VERSION 3.10)

# set the project name
project(BusStops)

# add the executable
add_executable(busStops main.cpp)

target_include_directories(busStops PUBLIC
                           /home/vika/projects/pub/src/utils/include/
                           )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
target_link_libraries(busStops_lib STATIC starter.cpp)

enable_testing()

add_subdirectory(tests)


