cmake_minimum_required(VERSION 3.10)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/PhoneNumber/googletest-src"
  BINARY_DIR        "/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/PhoneNumber/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
