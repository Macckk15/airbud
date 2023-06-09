# Install script for directory: /home/airbud/catkin_ws/src/Pangolin/Pangolin/examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/airbud/catkin_ws/devel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/airbud/catkin_ws/build/pangolin/examples/BasicOpenGL/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/HelloPangolin/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/HelloPangolinThreads/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplay/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/SimpleMultiDisplay/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/SimpleDisplayImage/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/SimplePlot/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/SimpleVideo/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/SimpleRecord/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/HelloPangolinOffscreen/cmake_install.cmake")
  include("/home/airbud/catkin_ws/build/pangolin/examples/SimpleScene/cmake_install.cmake")

endif()

