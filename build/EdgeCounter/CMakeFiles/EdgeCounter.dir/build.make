# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/condekind/repos/llvm-ep

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/condekind/repos/llvm-ep/build

# Include any dependencies generated for this target.
include EdgeCounter/CMakeFiles/EdgeCounter.dir/depend.make

# Include the progress variables for this target.
include EdgeCounter/CMakeFiles/EdgeCounter.dir/progress.make

# Include the compile flags for this target's objects.
include EdgeCounter/CMakeFiles/EdgeCounter.dir/flags.make

EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o: EdgeCounter/CMakeFiles/EdgeCounter.dir/flags.make
EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o: ../EdgeCounter/EdgeCounter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/condekind/repos/llvm-ep/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o"
	cd /home/condekind/repos/llvm-ep/build/EdgeCounter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o -c /home/condekind/repos/llvm-ep/EdgeCounter/EdgeCounter.cpp

EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.i"
	cd /home/condekind/repos/llvm-ep/build/EdgeCounter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/condekind/repos/llvm-ep/EdgeCounter/EdgeCounter.cpp > CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.i

EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.s"
	cd /home/condekind/repos/llvm-ep/build/EdgeCounter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/condekind/repos/llvm-ep/EdgeCounter/EdgeCounter.cpp -o CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.s

EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.requires:

.PHONY : EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.requires

EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.provides: EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.requires
	$(MAKE) -f EdgeCounter/CMakeFiles/EdgeCounter.dir/build.make EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.provides.build
.PHONY : EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.provides

EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.provides.build: EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o


# Object files for target EdgeCounter
EdgeCounter_OBJECTS = \
"CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o"

# External object files for target EdgeCounter
EdgeCounter_EXTERNAL_OBJECTS =

EdgeCounter/EdgeCounter.so: EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o
EdgeCounter/EdgeCounter.so: EdgeCounter/CMakeFiles/EdgeCounter.dir/build.make
EdgeCounter/EdgeCounter.so: EdgeCounter/CMakeFiles/EdgeCounter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/condekind/repos/llvm-ep/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module EdgeCounter.so"
	cd /home/condekind/repos/llvm-ep/build/EdgeCounter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EdgeCounter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
EdgeCounter/CMakeFiles/EdgeCounter.dir/build: EdgeCounter/EdgeCounter.so

.PHONY : EdgeCounter/CMakeFiles/EdgeCounter.dir/build

EdgeCounter/CMakeFiles/EdgeCounter.dir/requires: EdgeCounter/CMakeFiles/EdgeCounter.dir/EdgeCounter.cpp.o.requires

.PHONY : EdgeCounter/CMakeFiles/EdgeCounter.dir/requires

EdgeCounter/CMakeFiles/EdgeCounter.dir/clean:
	cd /home/condekind/repos/llvm-ep/build/EdgeCounter && $(CMAKE_COMMAND) -P CMakeFiles/EdgeCounter.dir/cmake_clean.cmake
.PHONY : EdgeCounter/CMakeFiles/EdgeCounter.dir/clean

EdgeCounter/CMakeFiles/EdgeCounter.dir/depend:
	cd /home/condekind/repos/llvm-ep/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/condekind/repos/llvm-ep /home/condekind/repos/llvm-ep/EdgeCounter /home/condekind/repos/llvm-ep/build /home/condekind/repos/llvm-ep/build/EdgeCounter /home/condekind/repos/llvm-ep/build/EdgeCounter/CMakeFiles/EdgeCounter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : EdgeCounter/CMakeFiles/EdgeCounter.dir/depend

