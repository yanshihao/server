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
include CMakeFiles/test16.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test16.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test16.dir/flags.make

CMakeFiles/test16.dir/test/test16.cc.o: CMakeFiles/test16.dir/flags.make
CMakeFiles/test16.dir/test/test16.cc.o: ../test/test16.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ysh/git/server/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test16.dir/test/test16.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test16.dir/test/test16.cc.o -c /home/ysh/git/server/server/test/test16.cc

CMakeFiles/test16.dir/test/test16.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test16.dir/test/test16.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ysh/git/server/server/test/test16.cc > CMakeFiles/test16.dir/test/test16.cc.i

CMakeFiles/test16.dir/test/test16.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test16.dir/test/test16.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ysh/git/server/server/test/test16.cc -o CMakeFiles/test16.dir/test/test16.cc.s

CMakeFiles/test16.dir/test/test16.cc.o.requires:

.PHONY : CMakeFiles/test16.dir/test/test16.cc.o.requires

CMakeFiles/test16.dir/test/test16.cc.o.provides: CMakeFiles/test16.dir/test/test16.cc.o.requires
	$(MAKE) -f CMakeFiles/test16.dir/build.make CMakeFiles/test16.dir/test/test16.cc.o.provides.build
.PHONY : CMakeFiles/test16.dir/test/test16.cc.o.provides

CMakeFiles/test16.dir/test/test16.cc.o.provides.build: CMakeFiles/test16.dir/test/test16.cc.o


# Object files for target test16
test16_OBJECTS = \
"CMakeFiles/test16.dir/test/test16.cc.o"

# External object files for target test16
test16_EXTERNAL_OBJECTS =

test16: CMakeFiles/test16.dir/test/test16.cc.o
test16: CMakeFiles/test16.dir/build.make
test16: libserver.a
test16: CMakeFiles/test16.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ysh/git/server/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test16"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test16.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test16.dir/build: test16

.PHONY : CMakeFiles/test16.dir/build

CMakeFiles/test16.dir/requires: CMakeFiles/test16.dir/test/test16.cc.o.requires

.PHONY : CMakeFiles/test16.dir/requires

CMakeFiles/test16.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test16.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test16.dir/clean

CMakeFiles/test16.dir/depend:
	cd /home/ysh/git/server/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ysh/git/server/server /home/ysh/git/server/server /home/ysh/git/server/server/build /home/ysh/git/server/server/build /home/ysh/git/server/server/build/CMakeFiles/test16.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test16.dir/depend

