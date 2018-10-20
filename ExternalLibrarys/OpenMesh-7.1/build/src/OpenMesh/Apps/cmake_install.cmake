# Install script for directory: /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/src/OpenMesh/Apps

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/B")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/Dualizer/cmake_install.cmake")
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/Decimating/commandlineDecimater/cmake_install.cmake")
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/Smoothing/cmake_install.cmake")
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineSubdivider/cmake_install.cmake")
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/Subdivider/commandlineAdaptiveSubdivider/cmake_install.cmake")
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert/cmake_install.cmake")
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/VDProgMesh/mkbalancedpm/cmake_install.cmake")
  include("/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/VDProgMesh/Analyzer/cmake_install.cmake")

endif()

