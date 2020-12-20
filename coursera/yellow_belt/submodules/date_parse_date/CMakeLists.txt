cmake_minimum_required(VERSION 3.10)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic -Werror)
include_directories( ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

enable_testing()
file(GLOB_RECURSE TESTS_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
find_package(GTest REQUIRED)
include(GoogleTest)
add_executable(${CMAKE_PROJECT_NAME}_tests ${TESTS_SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME}_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME}_lib)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_tests)
