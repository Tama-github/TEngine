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
CMAKE_SOURCE_DIR = /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build

# Utility rule file for ExperimentalMemCheck.

# Include the progress variables for this target.
include test/CMakeFiles/ExperimentalMemCheck.dir/progress.make

test/CMakeFiles/ExperimentalMemCheck:
	cd /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/test && /usr/bin/ctest -D ExperimentalMemCheck

ExperimentalMemCheck: test/CMakeFiles/ExperimentalMemCheck
ExperimentalMemCheck: test/CMakeFiles/ExperimentalMemCheck.dir/build.make

.PHONY : ExperimentalMemCheck

# Rule to build all files generated by this target.
test/CMakeFiles/ExperimentalMemCheck.dir/build: ExperimentalMemCheck

.PHONY : test/CMakeFiles/ExperimentalMemCheck.dir/build

test/CMakeFiles/ExperimentalMemCheck.dir/clean:
	cd /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/test && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalMemCheck.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/ExperimentalMemCheck.dir/clean

test/CMakeFiles/ExperimentalMemCheck.dir/depend:
	cd /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0 /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/test /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/test /home/tama/Moteure/animation/TEngine/ExternalLibraries/assimp-4.1.0/build/test/CMakeFiles/ExperimentalMemCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/ExperimentalMemCheck.dir/depend

