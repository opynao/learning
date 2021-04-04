cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER clang++)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic -Werror)

set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif()
 
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#set(CMAKE_CXX_CLANG_TIDY 
#       clang-tidy;
#       -header-filter=.;
#       -checks=*;)
  
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
