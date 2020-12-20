cmake_minimum_required(VERSION 3.10)

project(TestingPhoneNumber)


add_executable(testPhoneNumber PhoneNumberTests.cpp)
target_link_libraries(testPhoneNumber phoneNumber_lib)
add_test(NAME testPhoneNumber COMMAND testPhoneNumber)


