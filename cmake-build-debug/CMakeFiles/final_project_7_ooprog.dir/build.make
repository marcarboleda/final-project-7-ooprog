# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/renzocabral/Documents/final-project-7-ooprog.

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/renzocabral/Documents/final-project-7-ooprog./cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/final_project_7_ooprog.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/final_project_7_ooprog.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/final_project_7_ooprog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/final_project_7_ooprog.dir/flags.make

CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o: CMakeFiles/final_project_7_ooprog.dir/flags.make
CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o: /Users/renzocabral/Documents/final-project-7-ooprog./finals.cpp
CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o: CMakeFiles/final_project_7_ooprog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/renzocabral/Documents/final-project-7-ooprog./cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o -MF CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o.d -o CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o -c /Users/renzocabral/Documents/final-project-7-ooprog./finals.cpp

CMakeFiles/final_project_7_ooprog.dir/finals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final_project_7_ooprog.dir/finals.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renzocabral/Documents/final-project-7-ooprog./finals.cpp > CMakeFiles/final_project_7_ooprog.dir/finals.cpp.i

CMakeFiles/final_project_7_ooprog.dir/finals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final_project_7_ooprog.dir/finals.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renzocabral/Documents/final-project-7-ooprog./finals.cpp -o CMakeFiles/final_project_7_ooprog.dir/finals.cpp.s

# Object files for target final_project_7_ooprog
final_project_7_ooprog_OBJECTS = \
"CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o"

# External object files for target final_project_7_ooprog
final_project_7_ooprog_EXTERNAL_OBJECTS =

final_project_7_ooprog: CMakeFiles/final_project_7_ooprog.dir/finals.cpp.o
final_project_7_ooprog: CMakeFiles/final_project_7_ooprog.dir/build.make
final_project_7_ooprog: CMakeFiles/final_project_7_ooprog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/renzocabral/Documents/final-project-7-ooprog./cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable final_project_7_ooprog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/final_project_7_ooprog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/final_project_7_ooprog.dir/build: final_project_7_ooprog
.PHONY : CMakeFiles/final_project_7_ooprog.dir/build

CMakeFiles/final_project_7_ooprog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/final_project_7_ooprog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/final_project_7_ooprog.dir/clean

CMakeFiles/final_project_7_ooprog.dir/depend:
	cd /Users/renzocabral/Documents/final-project-7-ooprog./cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/renzocabral/Documents/final-project-7-ooprog. /Users/renzocabral/Documents/final-project-7-ooprog. /Users/renzocabral/Documents/final-project-7-ooprog./cmake-build-debug /Users/renzocabral/Documents/final-project-7-ooprog./cmake-build-debug /Users/renzocabral/Documents/final-project-7-ooprog./cmake-build-debug/CMakeFiles/final_project_7_ooprog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/final_project_7_ooprog.dir/depend

