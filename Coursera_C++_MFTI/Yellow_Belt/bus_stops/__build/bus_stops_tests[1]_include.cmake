if(EXISTS "/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/BusStopsCopy/BusStops/bus_stops/__build/bus_stops_tests[1]_tests.cmake")
  include("/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/BusStopsCopy/BusStops/bus_stops/__build/bus_stops_tests[1]_tests.cmake")
else()
  add_test(bus_stops_tests_NOT_BUILT bus_stops_tests_NOT_BUILT)
endif()
