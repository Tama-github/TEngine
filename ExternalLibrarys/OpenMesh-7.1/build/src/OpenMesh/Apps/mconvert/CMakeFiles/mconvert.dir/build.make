# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build

# Include any dependencies generated for this target.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend.make

# Include the progress variables for this target.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/progress.make

# Include the compile flags for this target's objects.
include src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/flags.make

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/flags.make
src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o: ../src/OpenMesh/Apps/mconvert/mconvert.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o"
	cd /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mconvert.dir/mconvert.cc.o -c /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/src/OpenMesh/Apps/mconvert/mconvert.cc

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mconvert.dir/mconvert.cc.i"
	cd /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/src/OpenMesh/Apps/mconvert/mconvert.cc > CMakeFiles/mconvert.dir/mconvert.cc.i

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mconvert.dir/mconvert.cc.s"
	cd /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/src/OpenMesh/Apps/mconvert/mconvert.cc -o CMakeFiles/mconvert.dir/mconvert.cc.s

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires:

.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires
	$(MAKE) -f src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build.make src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides.build
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.provides.build: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o


# Object files for target mconvert
mconvert_OBJECTS = \
"CMakeFiles/mconvert.dir/mconvert.cc.o"

# External object files for target mconvert
mconvert_EXTERNAL_OBJECTS =

Build/bin/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o
Build/bin/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build.make
Build/bin/mconvert: Build/lib/libOpenMeshTools.so.7.1
Build/bin/mconvert: Build/lib/libOpenMeshCore.so.7.1
Build/bin/mconvert: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../Build/bin/mconvert"
	cd /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mconvert.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build: Build/bin/mconvert

.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/build

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/requires: src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/mconvert.cc.o.requires

.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/requires

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/clean:
	cd /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert && $(CMAKE_COMMAND) -P CMakeFiles/mconvert.dir/cmake_clean.cmake
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/clean

src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend:
	cd /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1 /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/src/OpenMesh/Apps/mconvert /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert /home/tama/Moteure/animation/TEngine/ExternalLibrarys/OpenMesh-7.1/build/src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/OpenMesh/Apps/mconvert/CMakeFiles/mconvert.dir/depend

