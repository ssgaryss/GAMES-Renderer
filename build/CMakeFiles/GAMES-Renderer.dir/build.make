# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\build

# Include any dependencies generated for this target.
include CMakeFiles/GAMES-Renderer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GAMES-Renderer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GAMES-Renderer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GAMES-Renderer.dir/flags.make

CMakeFiles/GAMES-Renderer.dir/main.cpp.obj: CMakeFiles/GAMES-Renderer.dir/flags.make
CMakeFiles/GAMES-Renderer.dir/main.cpp.obj: D:/Master_Learning_Qiuhuidi/Projects/GAMES-Renderer/main.cpp
CMakeFiles/GAMES-Renderer.dir/main.cpp.obj: CMakeFiles/GAMES-Renderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GAMES-Renderer.dir/main.cpp.obj"
	C:\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GAMES-Renderer.dir/main.cpp.obj -MF CMakeFiles\GAMES-Renderer.dir\main.cpp.obj.d -o CMakeFiles\GAMES-Renderer.dir\main.cpp.obj -c D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\main.cpp

CMakeFiles/GAMES-Renderer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GAMES-Renderer.dir/main.cpp.i"
	C:\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\main.cpp > CMakeFiles\GAMES-Renderer.dir\main.cpp.i

CMakeFiles/GAMES-Renderer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GAMES-Renderer.dir/main.cpp.s"
	C:\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\main.cpp -o CMakeFiles\GAMES-Renderer.dir\main.cpp.s

# Object files for target GAMES-Renderer
GAMES__Renderer_OBJECTS = \
"CMakeFiles/GAMES-Renderer.dir/main.cpp.obj"

# External object files for target GAMES-Renderer
GAMES__Renderer_EXTERNAL_OBJECTS =

GAMES-Renderer.exe: CMakeFiles/GAMES-Renderer.dir/main.cpp.obj
GAMES-Renderer.exe: CMakeFiles/GAMES-Renderer.dir/build.make
GAMES-Renderer.exe: CMakeFiles/GAMES-Renderer.dir/linkLibs.rsp
GAMES-Renderer.exe: CMakeFiles/GAMES-Renderer.dir/objects1.rsp
GAMES-Renderer.exe: CMakeFiles/GAMES-Renderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GAMES-Renderer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GAMES-Renderer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GAMES-Renderer.dir/build: GAMES-Renderer.exe
.PHONY : CMakeFiles/GAMES-Renderer.dir/build

CMakeFiles/GAMES-Renderer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GAMES-Renderer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GAMES-Renderer.dir/clean

CMakeFiles/GAMES-Renderer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\build D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\build D:\Master_Learning_Qiuhuidi\Projects\GAMES-Renderer\build\CMakeFiles\GAMES-Renderer.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GAMES-Renderer.dir/depend
