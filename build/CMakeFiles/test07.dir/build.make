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
include CMakeFiles/test07.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test07.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test07.dir/flags.make

CMakeFiles/test07.dir/test/test07.cc.o: CMakeFiles/test07.dir/flags.make
CMakeFiles/test07.dir/test/test07.cc.o: ../test/test07.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ysh/git/server/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test07.dir/test/test07.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test07.dir/test/test07.cc.o -c /home/ysh/git/server/server/test/test07.cc

CMakeFiles/test07.dir/test/test07.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test07.dir/test/test07.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ysh/git/server/server/test/test07.cc > CMakeFiles/test07.dir/test/test07.cc.i

CMakeFiles/test07.dir/test/test07.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test07.dir/test/test07.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ysh/git/server/server/test/test07.cc -o CMakeFiles/test07.dir/test/test07.cc.s

CMakeFiles/test07.dir/test/test07.cc.o.requires:

.PHONY : CMakeFiles/test07.dir/test/test07.cc.o.requires

CMakeFiles/test07.dir/test/test07.cc.o.provides: CMakeFiles/test07.dir/test/test07.cc.o.requires
	$(MAKE) -f CMakeFiles/test07.dir/build.make CMakeFiles/test07.dir/test/test07.cc.o.provides.build
.PHONY : CMakeFiles/test07.dir/test/test07.cc.o.provides

CMakeFiles/test07.dir/test/test07.cc.o.provides.build: CMakeFiles/test07.dir/test/test07.cc.o


# Object files for target test07
test07_OBJECTS = \
"CMakeFiles/test07.dir/test/test07.cc.o"

# External object files for target test07
test07_EXTERNAL_OBJECTS =

test07: CMakeFiles/test07.dir/test/test07.cc.o
test07: CMakeFiles/test07.dir/build.make
test07: libserver.a
test07: CMakeFiles/test07.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ysh/git/server/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test07"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test07.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test07.dir/build: test07

.PHONY : CMakeFiles/test07.dir/build

CMakeFiles/test07.dir/requires: CMakeFiles/test07.dir/test/test07.cc.o.requires

.PHONY : CMakeFiles/test07.dir/requires

CMakeFiles/test07.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test07.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test07.dir/clean

CMakeFiles/test07.dir/depend:
	cd /home/ysh/git/server/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ysh/git/server/server /home/ysh/git/server/server /home/ysh/git/server/server/build /home/ysh/git/server/server/build /home/ysh/git/server/server/build/CMakeFiles/test07.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test07.dir/depend

