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
include CMakeFiles/pango_python.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pango_python.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pango_python.dir/flags.make

CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o: CMakeFiles/pango_python.dir/flags.make
CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o: /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_core/src/dummy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/airbud/catkin_ws/build/pangolin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o -c /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_core/src/dummy.cpp

CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_core/src/dummy.cpp > CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.i

CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_core/src/dummy.cpp -o CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.s

CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.requires:

.PHONY : CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.requires

CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.provides: CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.requires
	$(MAKE) -f CMakeFiles/pango_python.dir/build.make CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.provides.build
.PHONY : CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.provides

CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.provides.build: CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o


# Object files for target pango_python
pango_python_OBJECTS = \
"CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o"

# External object files for target pango_python
pango_python_EXTERNAL_OBJECTS =

libpango_python.so: CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o
libpango_python.so: CMakeFiles/pango_python.dir/build.make
libpango_python.so: CMakeFiles/pango_python.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/airbud/catkin_ws/build/pangolin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libpango_python.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pango_python.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pango_python.dir/build: libpango_python.so

.PHONY : CMakeFiles/pango_python.dir/build

CMakeFiles/pango_python.dir/requires: CMakeFiles/pango_python.dir/components/pango_core/src/dummy.cpp.o.requires

.PHONY : CMakeFiles/pango_python.dir/requires

CMakeFiles/pango_python.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pango_python.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pango_python.dir/clean

CMakeFiles/pango_python.dir/depend:
	cd /home/airbud/catkin_ws/build/pangolin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/airbud/catkin_ws/src/Pangolin/Pangolin /home/airbud/catkin_ws/src/Pangolin/Pangolin /home/airbud/catkin_ws/build/pangolin /home/airbud/catkin_ws/build/pangolin /home/airbud/catkin_ws/build/pangolin/CMakeFiles/pango_python.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pango_python.dir/depend

