# Install script for directory: /home/airbud/catkin_ws/src/eigen-3.3.7/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE FILE FILES
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Cholesky"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/CholmodSupport"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Core"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Dense"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Eigen"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Eigenvalues"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Geometry"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Householder"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/IterativeLinearSolvers"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Jacobi"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/LU"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/MetisSupport"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/OrderingMethods"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/PaStiXSupport"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/PardisoSupport"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/QR"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/QtAlignedMalloc"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/SPQRSupport"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/SVD"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/Sparse"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/SparseCholesky"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/SparseCore"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/SparseLU"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/SparseQR"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/StdDeque"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/StdList"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/StdVector"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/SuperLUSupport"
    "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/UmfPackSupport"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE DIRECTORY FILES "/home/airbud/catkin_ws/src/eigen-3.3.7/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

