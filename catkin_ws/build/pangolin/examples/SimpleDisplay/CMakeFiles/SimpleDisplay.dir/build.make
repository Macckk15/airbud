# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/airbud/catkin_ws/src/Pangolin/Pangolin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/airbud/catkin_ws/build/pangolin

# Include any dependencies generated for this target.
include examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/depend.make

# Include the progress variables for this target.
include examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/progress.make

# Include the compile flags for this target's objects.
include examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/flags.make

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o: examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/flags.make
examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o: /home/airbud/catkin_ws/src/Pangolin/Pangolin/examples/SimpleDisplay/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/airbud/catkin_ws/build/pangolin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o"
	cd /home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimpleDisplay.dir/main.cpp.o -c /home/airbud/catkin_ws/src/Pangolin/Pangolin/examples/SimpleDisplay/main.cpp

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimpleDisplay.dir/main.cpp.i"
	cd /home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/airbud/catkin_ws/src/Pangolin/Pangolin/examples/SimpleDisplay/main.cpp > CMakeFiles/SimpleDisplay.dir/main.cpp.i

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimpleDisplay.dir/main.cpp.s"
	cd /home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/airbud/catkin_ws/src/Pangolin/Pangolin/examples/SimpleDisplay/main.cpp -o CMakeFiles/SimpleDisplay.dir/main.cpp.s

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.requires:

.PHONY : examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.requires

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.provides: examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.requires
	$(MAKE) -f examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/build.make examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.provides.build
.PHONY : examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.provides

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.provides.build: examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o


# Object files for target SimpleDisplay
SimpleDisplay_OBJECTS = \
"CMakeFiles/SimpleDisplay.dir/main.cpp.o"

# External object files for target SimpleDisplay
SimpleDisplay_EXTERNAL_OBJECTS =

examples/SimpleDisplay/SimpleDisplay: examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o
examples/SimpleDisplay/SimpleDisplay: examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/build.make
examples/SimpleDisplay/SimpleDisplay: libpango_display.so
examples/SimpleDisplay/SimpleDisplay: libpango_python.so
examples/SimpleDisplay/SimpleDisplay: libpango_windowing.so
examples/SimpleDisplay/SimpleDisplay: libpango_opengl.so
examples/SimpleDisplay/SimpleDisplay: libpango_image.so
examples/SimpleDisplay/SimpleDisplay: /usr/lib/aarch64-linux-gnu/libGLEW.so
examples/SimpleDisplay/SimpleDisplay: /usr/lib/aarch64-linux-gnu/libOpenGL.so
examples/SimpleDisplay/SimpleDisplay: /usr/lib/aarch64-linux-gnu/libGLX.so
examples/SimpleDisplay/SimpleDisplay: /usr/lib/aarch64-linux-gnu/libGLU.so
examples/SimpleDisplay/SimpleDisplay: libpango_vars.so
examples/SimpleDisplay/SimpleDisplay: libpango_core.so
examples/SimpleDisplay/SimpleDisplay: examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/airbud/catkin_ws/build/pangolin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SimpleDisplay"
	cd /home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimpleDisplay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/build: examples/SimpleDisplay/SimpleDisplay

.PHONY : examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/build

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/requires: examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/main.cpp.o.requires

.PHONY : examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/requires

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/clean:
	cd /home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay && $(CMAKE_COMMAND) -P CMakeFiles/SimpleDisplay.dir/cmake_clean.cmake
.PHONY : examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/clean

examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/depend:
	cd /home/airbud/catkin_ws/build/pangolin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/airbud/catkin_ws/src/Pangolin/Pangolin /home/airbud/catkin_ws/src/Pangolin/Pangolin/examples/SimpleDisplay /home/airbud/catkin_ws/build/pangolin /home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay /home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/SimpleDisplay/CMakeFiles/SimpleDisplay.dir/depend

