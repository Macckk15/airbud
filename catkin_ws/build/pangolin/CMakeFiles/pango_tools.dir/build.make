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
include CMakeFiles/pango_tools.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pango_tools.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pango_tools.dir/flags.make

CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o: CMakeFiles/pango_tools.dir/flags.make
CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o: /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_tools/src/video_viewer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/airbud/catkin_ws/build/pangolin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o -c /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_tools/src/video_viewer.cpp

CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_tools/src/video_viewer.cpp > CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.i

CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/airbud/catkin_ws/src/Pangolin/Pangolin/components/pango_tools/src/video_viewer.cpp -o CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.s

CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.requires:

.PHONY : CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.requires

CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.provides: CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.requires
	$(MAKE) -f CMakeFiles/pango_tools.dir/build.make CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.provides.build
.PHONY : CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.provides

CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.provides.build: CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o


# Object files for target pango_tools
pango_tools_OBJECTS = \
"CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o"

# External object files for target pango_tools
pango_tools_EXTERNAL_OBJECTS =

libpango_tools.so: CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o
libpango_tools.so: CMakeFiles/pango_tools.dir/build.make
libpango_tools.so: libpango_display.so
libpango_tools.so: libpango_video.so
libpango_tools.so: libpango_windowing.so
libpango_tools.so: libpango_opengl.so
libpango_tools.so: /usr/lib/aarch64-linux-gnu/libGLEW.so
libpango_tools.so: /usr/lib/aarch64-linux-gnu/libOpenGL.so
libpango_tools.so: /usr/lib/aarch64-linux-gnu/libGLX.so
libpango_tools.so: /usr/lib/aarch64-linux-gnu/libGLU.so
libpango_tools.so: libpango_vars.so
libpango_tools.so: libpango_image.so
libpango_tools.so: libpango_packetstream.so
libpango_tools.so: libpango_core.so
libpango_tools.so: CMakeFiles/pango_tools.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/airbud/catkin_ws/build/pangolin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libpango_tools.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pango_tools.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pango_tools.dir/build: libpango_tools.so

.PHONY : CMakeFiles/pango_tools.dir/build

CMakeFiles/pango_tools.dir/requires: CMakeFiles/pango_tools.dir/components/pango_tools/src/video_viewer.cpp.o.requires

.PHONY : CMakeFiles/pango_tools.dir/requires

CMakeFiles/pango_tools.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pango_tools.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pango_tools.dir/clean

CMakeFiles/pango_tools.dir/depend:
	cd /home/airbud/catkin_ws/build/pangolin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/airbud/catkin_ws/src/Pangolin/Pangolin /home/airbud/catkin_ws/src/Pangolin/Pangolin /home/airbud/catkin_ws/build/pangolin /home/airbud/catkin_ws/build/pangolin /home/airbud/catkin_ws/build/pangolin/CMakeFiles/pango_tools.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pango_tools.dir/depend

