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
CMAKE_SOURCE_DIR = /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/airbud/catkin_ws/build/imu_filter_madgwick

# Include any dependencies generated for this target.
include CMakeFiles/imu_filter_madgwick-madgwick_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/imu_filter_madgwick-madgwick_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imu_filter_madgwick-madgwick_test.dir/flags.make

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/flags.make
CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o: /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/stateless_orientation_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/airbud/catkin_ws/build/imu_filter_madgwick/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o -c /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/stateless_orientation_test.cpp

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/stateless_orientation_test.cpp > CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.i

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/stateless_orientation_test.cpp -o CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.s

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.requires:

.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.requires

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.provides: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/imu_filter_madgwick-madgwick_test.dir/build.make CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.provides.build
.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.provides

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.provides.build: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o


CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/flags.make
CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o: /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/madgwick_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/airbud/catkin_ws/build/imu_filter_madgwick/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o -c /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/madgwick_test.cpp

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/madgwick_test.cpp > CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.i

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick/test/madgwick_test.cpp -o CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.s

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.requires:

.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.requires

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.provides: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/imu_filter_madgwick-madgwick_test.dir/build.make CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.provides.build
.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.provides

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.provides.build: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o


# Object files for target imu_filter_madgwick-madgwick_test
imu_filter_madgwick__madgwick_test_OBJECTS = \
"CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o" \
"CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o"

# External object files for target imu_filter_madgwick-madgwick_test
imu_filter_madgwick__madgwick_test_EXTERNAL_OBJECTS =

/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/build.make
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: gtest/googlemock/gtest/libgtest.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/libimu_filter.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libdynamic_reconfigure_config_init_mutex.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libnodeletlib.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libbondcpp.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libuuid.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libclass_loader.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/libPocoFoundation.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libdl.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libroslib.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/librospack.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libpython2.7.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_program_options.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libtinyxml2.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/liborocos-kdl.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/liborocos-kdl.so.1.4.0
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libtf2_ros.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libactionlib.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libmessage_filters.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libroscpp.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/librosconsole.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_regex.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libtf2.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/librostime.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /opt/ros/melodic/lib/libcpp_common.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_system.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_thread.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_chrono.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_date_time.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libboost_atomic.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/airbud/catkin_ws/build/imu_filter_madgwick/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imu_filter_madgwick-madgwick_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imu_filter_madgwick-madgwick_test.dir/build: /home/airbud/catkin_ws/devel/.private/imu_filter_madgwick/lib/imu_filter_madgwick/imu_filter_madgwick-madgwick_test

.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/build

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/requires: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/stateless_orientation_test.cpp.o.requires
CMakeFiles/imu_filter_madgwick-madgwick_test.dir/requires: CMakeFiles/imu_filter_madgwick-madgwick_test.dir/test/madgwick_test.cpp.o.requires

.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/requires

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imu_filter_madgwick-madgwick_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/clean

CMakeFiles/imu_filter_madgwick-madgwick_test.dir/depend:
	cd /home/airbud/catkin_ws/build/imu_filter_madgwick && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick /home/airbud/catkin_ws/src/imu_tools/imu_filter_madgwick /home/airbud/catkin_ws/build/imu_filter_madgwick /home/airbud/catkin_ws/build/imu_filter_madgwick /home/airbud/catkin_ws/build/imu_filter_madgwick/CMakeFiles/imu_filter_madgwick-madgwick_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imu_filter_madgwick-madgwick_test.dir/depend

