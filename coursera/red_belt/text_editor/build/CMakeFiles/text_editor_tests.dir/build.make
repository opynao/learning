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
CMAKE_SOURCE_DIR = /home/vika/learning/coursera/red_belt/text_editor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vika/learning/coursera/red_belt/text_editor/build

# Include any dependencies generated for this target.
include CMakeFiles/text_editor_tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/text_editor_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/text_editor_tests.dir/flags.make

CMakeFiles/text_editor_tests.dir/tests/test.cpp.o: CMakeFiles/text_editor_tests.dir/flags.make
CMakeFiles/text_editor_tests.dir/tests/test.cpp.o: ../tests/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vika/learning/coursera/red_belt/text_editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/text_editor_tests.dir/tests/test.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/text_editor_tests.dir/tests/test.cpp.o -c /home/vika/learning/coursera/red_belt/text_editor/tests/test.cpp

CMakeFiles/text_editor_tests.dir/tests/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/text_editor_tests.dir/tests/test.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vika/learning/coursera/red_belt/text_editor/tests/test.cpp > CMakeFiles/text_editor_tests.dir/tests/test.cpp.i

CMakeFiles/text_editor_tests.dir/tests/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/text_editor_tests.dir/tests/test.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vika/learning/coursera/red_belt/text_editor/tests/test.cpp -o CMakeFiles/text_editor_tests.dir/tests/test.cpp.s

# Object files for target text_editor_tests
text_editor_tests_OBJECTS = \
"CMakeFiles/text_editor_tests.dir/tests/test.cpp.o"

# External object files for target text_editor_tests
text_editor_tests_EXTERNAL_OBJECTS =

text_editor_tests: CMakeFiles/text_editor_tests.dir/tests/test.cpp.o
text_editor_tests: CMakeFiles/text_editor_tests.dir/build.make
text_editor_tests: /usr/lib/x86_64-linux-gnu/libgtest.a
text_editor_tests: /usr/lib/x86_64-linux-gnu/libgtest_main.a
text_editor_tests: libtext_editor_lib.a
text_editor_tests: /usr/lib/x86_64-linux-gnu/libgtest.a
text_editor_tests: CMakeFiles/text_editor_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vika/learning/coursera/red_belt/text_editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable text_editor_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/text_editor_tests.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=text_editor_tests -D TEST_EXECUTABLE=/home/vika/learning/coursera/red_belt/text_editor/build/text_editor_tests -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/vika/learning/coursera/red_belt/text_editor/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=text_editor_tests_TESTS -D CTEST_FILE=/home/vika/learning/coursera/red_belt/text_editor/build/text_editor_tests[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -P /usr/share/cmake-3.13/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/text_editor_tests.dir/build: text_editor_tests

.PHONY : CMakeFiles/text_editor_tests.dir/build

CMakeFiles/text_editor_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/text_editor_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/text_editor_tests.dir/clean

CMakeFiles/text_editor_tests.dir/depend:
	cd /home/vika/learning/coursera/red_belt/text_editor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vika/learning/coursera/red_belt/text_editor /home/vika/learning/coursera/red_belt/text_editor /home/vika/learning/coursera/red_belt/text_editor/build /home/vika/learning/coursera/red_belt/text_editor/build /home/vika/learning/coursera/red_belt/text_editor/build/CMakeFiles/text_editor_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/text_editor_tests.dir/depend

