# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Projects\Visualizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Projects\Visualizer\cmake-build-debug

# Utility rule file for NightlyMemoryCheck.

# Include any custom commands dependencies for this target.
include external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/compiler_depend.make

# Include the progress variables for this target.
include external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/progress.make

external/rtaudio/CMakeFiles/NightlyMemoryCheck:
	cd /d C:\Projects\Visualizer\cmake-build-debug\external\rtaudio && "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\ctest.exe" -D NightlyMemoryCheck

NightlyMemoryCheck: external/rtaudio/CMakeFiles/NightlyMemoryCheck
NightlyMemoryCheck: external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/build.make
.PHONY : NightlyMemoryCheck

# Rule to build all files generated by this target.
external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/build: NightlyMemoryCheck
.PHONY : external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/build

external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/clean:
	cd /d C:\Projects\Visualizer\cmake-build-debug\external\rtaudio && $(CMAKE_COMMAND) -P CMakeFiles\NightlyMemoryCheck.dir\cmake_clean.cmake
.PHONY : external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/clean

external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Projects\Visualizer C:\Projects\Visualizer\external\rtaudio C:\Projects\Visualizer\cmake-build-debug C:\Projects\Visualizer\cmake-build-debug\external\rtaudio C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\CMakeFiles\NightlyMemoryCheck.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : external/rtaudio/CMakeFiles/NightlyMemoryCheck.dir/depend

