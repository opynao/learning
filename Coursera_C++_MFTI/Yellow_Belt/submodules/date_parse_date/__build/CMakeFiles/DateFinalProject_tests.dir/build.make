# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build

# Include any dependencies generated for this target.
include CMakeFiles/DateFinalProject_tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DateFinalProject_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DateFinalProject_tests.dir/flags.make

CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.o: CMakeFiles/DateFinalProject_tests.dir/flags.make
CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.o: ../tests/date_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.o -c /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/tests/date_test.cpp

CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/tests/date_test.cpp > CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.i

CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/tests/date_test.cpp -o CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.s

# Object files for target DateFinalProject_tests
DateFinalProject_tests_OBJECTS = \
"CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.o"

# External object files for target DateFinalProject_tests
DateFinalProject_tests_EXTERNAL_OBJECTS =

DateFinalProject_tests: CMakeFiles/DateFinalProject_tests.dir/tests/date_test.cpp.o
DateFinalProject_tests: CMakeFiles/DateFinalProject_tests.dir/build.make
DateFinalProject_tests: /usr/lib/x86_64-linux-gnu/libgtest.a
DateFinalProject_tests: /usr/lib/x86_64-linux-gnu/libgtest_main.a
DateFinalProject_tests: libDateFinalProject_lib.a
DateFinalProject_tests: /usr/lib/x86_64-linux-gnu/libgtest.a
DateFinalProject_tests: CMakeFiles/DateFinalProject_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DateFinalProject_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DateFinalProject_tests.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=DateFinalProject_tests -D TEST_EXECUTABLE=/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build/DateFinalProject_tests -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=DateFinalProject_tests_TESTS -D CTEST_FILE=/home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build/DateFinalProject_tests[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -P /usr/share/cmake-3.13/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/DateFinalProject_tests.dir/build: DateFinalProject_tests

.PHONY : CMakeFiles/DateFinalProject_tests.dir/build

CMakeFiles/DateFinalProject_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DateFinalProject_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DateFinalProject_tests.dir/clean

CMakeFiles/DateFinalProject_tests.dir/depend:
	cd /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build /home/vika/Learning/Coursera_C++_MFTI/Yellow_Belt/DateFinalProject/__build/CMakeFiles/DateFinalProject_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DateFinalProject_tests.dir/depend
