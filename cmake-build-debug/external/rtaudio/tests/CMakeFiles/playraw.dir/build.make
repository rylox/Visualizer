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

# Include any dependencies generated for this target.
include external/rtaudio/tests/CMakeFiles/playraw.dir/depend.make
# Include the progress variables for this target.
include external/rtaudio/tests/CMakeFiles/playraw.dir/progress.make

# Include the compile flags for this target's objects.
include external/rtaudio/tests/CMakeFiles/playraw.dir/flags.make

external/rtaudio/tests/CMakeFiles/playraw.dir/playraw.cpp.obj: external/rtaudio/tests/CMakeFiles/playraw.dir/flags.make
external/rtaudio/tests/CMakeFiles/playraw.dir/playraw.cpp.obj: external/rtaudio/tests/CMakeFiles/playraw.dir/includes_CXX.rsp
external/rtaudio/tests/CMakeFiles/playraw.dir/playraw.cpp.obj: ../external/rtaudio/tests/playraw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Projects\Visualizer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/rtaudio/tests/CMakeFiles/playraw.dir/playraw.cpp.obj"
	cd /d C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\playraw.dir\playraw.cpp.obj -c C:\Projects\Visualizer\external\rtaudio\tests\playraw.cpp

external/rtaudio/tests/CMakeFiles/playraw.dir/playraw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/playraw.dir/playraw.cpp.i"
	cd /d C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Projects\Visualizer\external\rtaudio\tests\playraw.cpp > CMakeFiles\playraw.dir\playraw.cpp.i

external/rtaudio/tests/CMakeFiles/playraw.dir/playraw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/playraw.dir/playraw.cpp.s"
	cd /d C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Projects\Visualizer\external\rtaudio\tests\playraw.cpp -o CMakeFiles\playraw.dir\playraw.cpp.s

# Object files for target playraw
playraw_OBJECTS = \
"CMakeFiles/playraw.dir/playraw.cpp.obj"

# External object files for target playraw
playraw_EXTERNAL_OBJECTS =

external/rtaudio/tests/playraw.exe: external/rtaudio/tests/CMakeFiles/playraw.dir/playraw.cpp.obj
external/rtaudio/tests/playraw.exe: external/rtaudio/tests/CMakeFiles/playraw.dir/build.make
external/rtaudio/tests/playraw.exe: external/rtaudio/librtaudiod.a
external/rtaudio/tests/playraw.exe: external/rtaudio/tests/CMakeFiles/playraw.dir/linklibs.rsp
external/rtaudio/tests/playraw.exe: external/rtaudio/tests/CMakeFiles/playraw.dir/objects1.rsp
external/rtaudio/tests/playraw.exe: external/rtaudio/tests/CMakeFiles/playraw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Projects\Visualizer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable playraw.exe"
	cd /d C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\playraw.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/rtaudio/tests/CMakeFiles/playraw.dir/build: external/rtaudio/tests/playraw.exe
.PHONY : external/rtaudio/tests/CMakeFiles/playraw.dir/build

external/rtaudio/tests/CMakeFiles/playraw.dir/clean:
	cd /d C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\tests && $(CMAKE_COMMAND) -P CMakeFiles\playraw.dir\cmake_clean.cmake
.PHONY : external/rtaudio/tests/CMakeFiles/playraw.dir/clean

external/rtaudio/tests/CMakeFiles/playraw.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Projects\Visualizer C:\Projects\Visualizer\external\rtaudio\tests C:\Projects\Visualizer\cmake-build-debug C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\tests C:\Projects\Visualizer\cmake-build-debug\external\rtaudio\tests\CMakeFiles\playraw.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : external/rtaudio/tests/CMakeFiles/playraw.dir/depend
