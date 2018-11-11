# Install script for directory: /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/B")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/code/libassimp.so.4.1.0"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/code/libassimp.so.4"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/code/libassimp.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/anim.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/ai_assert.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/camera.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/color4.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/color4.inl"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/code/../include/assimp/config.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/defs.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/Defines.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/cfileio.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/light.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/material.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/material.inl"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/matrix3x3.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/matrix3x3.inl"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/matrix4x4.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/matrix4x4.inl"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/mesh.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/postprocess.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/quaternion.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/quaternion.inl"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/scene.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/metadata.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/texture.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/types.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/vector2.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/vector2.inl"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/vector3.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/vector3.inl"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/version.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/cimport.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/importerdesc.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/Importer.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/DefaultLogger.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/ProgressHandler.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/IOStream.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/IOSystem.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/Logger.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/LogStream.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/NullLogger.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/cexport.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/Exporter.hpp"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/DefaultIOStream.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/DefaultIOSystem.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/SceneCombiner.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/Compiler/pushpack1.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/Compiler/poppack1.h"
    "/home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

