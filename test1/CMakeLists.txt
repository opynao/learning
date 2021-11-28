cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_COMPILER clang++-13)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors -w -Wextra -Wall -Waddress")

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib ${SRC_FILES})
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

enable_testing()
file(GLOB_RECURSE TESTS_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
find_package(GTest REQUIRED)
include(GoogleTest)
add_executable(${CMAKE_PROJECT_NAME}_tests ${TESTS_SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME}_tests GTest::GTest GTest::Main GTest::gmock GTest::gmock_main ${CMAKE_PROJECT_NAME}_lib)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_tests)
find_package (Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})