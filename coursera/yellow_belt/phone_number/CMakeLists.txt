cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER clang++)

project(PhoneNumber)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(INSTALL_GTEST OFF)
add_subdirectory(googletest)

add_executable(PhoneNumber main.cpp)
add_executable(PhoneNumber tests/PhoneNumberTests.cpp)

add_library(phoneNumber_lib phone_number.cpp)

target_link_libraries(PhoneNumber phoneNumber_lib)
target_link_libraries(PhoneNumber gtest)

enable_testing()

add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
