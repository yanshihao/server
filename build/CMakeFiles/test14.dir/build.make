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
CMAKE_SOURCE_DIR = /home/ysh/git/server/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ysh/git/server/server/build

# Include any dependencies generated for this target.
include CMakeFiles/test14.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test14.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test14.dir/flags.make

CMakeFiles/test14.dir/test/test14.cc.o: CMakeFiles/test14.dir/flags.make
CMakeFiles/test14.dir/test/test14.cc.o: ../test/test14.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ysh/git/server/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test14.dir/test/test14.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test14.dir/test/test14.cc.o -c /home/ysh/git/server/server/test/test14.cc

CMakeFiles/test14.dir/test/test14.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test14.dir/test/test14.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ysh/git/server/server/test/test14.cc > CMakeFiles/test14.dir/test/test14.cc.i

CMakeFiles/test14.dir/test/test14.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test14.dir/test/test14.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ysh/git/server/server/test/test14.cc -o CMakeFiles/test14.dir/test/test14.cc.s

CMakeFiles/test14.dir/test/test14.cc.o.requires:

.PHONY : CMakeFiles/test14.dir/test/test14.cc.o.requires

CMakeFiles/test14.dir/test/test14.cc.o.provides: CMakeFiles/test14.dir/test/test14.cc.o.requires
	$(MAKE) -f CMakeFiles/test14.dir/build.make CMakeFiles/test14.dir/test/test14.cc.o.provides.build
.PHONY : CMakeFiles/test14.dir/test/test14.cc.o.provides

CMakeFiles/test14.dir/test/test14.cc.o.provides.build: CMakeFiles/test14.dir/test/test14.cc.o


# Object files for target test14
test14_OBJECTS = \
"CMakeFiles/test14.dir/test/test14.cc.o"

# External object files for target test14
test14_EXTERNAL_OBJECTS =

test14: CMakeFiles/test14.dir/test/test14.cc.o
test14: CMakeFiles/test14.dir/build.make
test14: libserver.a
test14: CMakeFiles/test14.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ysh/git/server/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test14"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test14.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test14.dir/build: test14

.PHONY : CMakeFiles/test14.dir/build

CMakeFiles/test14.dir/requires: CMakeFiles/test14.dir/test/test14.cc.o.requires

.PHONY : CMakeFiles/test14.dir/requires

CMakeFiles/test14.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test14.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test14.dir/clean

CMakeFiles/test14.dir/depend:
	cd /home/ysh/git/server/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ysh/git/server/server /home/ysh/git/server/server /home/ysh/git/server/server/build /home/ysh/git/server/server/build /home/ysh/git/server/server/build/CMakeFiles/test14.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test14.dir/depend

