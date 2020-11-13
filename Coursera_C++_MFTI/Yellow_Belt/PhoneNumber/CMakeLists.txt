cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER clang++)

project(PhoneNumber)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(phoneNumber main.cpp)

add_library(phoneNumber_lib phone_number.cpp)

target_link_libraries(phoneNumber phoneNumber_lib)

enable_testing()

add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
