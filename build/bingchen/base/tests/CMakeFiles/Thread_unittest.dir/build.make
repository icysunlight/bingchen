# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/code/bingchen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/code/bingchen/build

# Include any dependencies generated for this target.
include bingchen/base/tests/CMakeFiles/Thread_unittest.dir/depend.make

# Include the progress variables for this target.
include bingchen/base/tests/CMakeFiles/Thread_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include bingchen/base/tests/CMakeFiles/Thread_unittest.dir/flags.make

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o: bingchen/base/tests/CMakeFiles/Thread_unittest.dir/flags.make
bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o: ../bingchen/base/tests/Thread_unittest.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/code/bingchen/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o"
	cd /root/code/bingchen/build/bingchen/base/tests && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o -c /root/code/bingchen/bingchen/base/tests/Thread_unittest.cc

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.i"
	cd /root/code/bingchen/build/bingchen/base/tests && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/code/bingchen/bingchen/base/tests/Thread_unittest.cc > CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.i

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.s"
	cd /root/code/bingchen/build/bingchen/base/tests && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/code/bingchen/bingchen/base/tests/Thread_unittest.cc -o CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.s

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.requires:
.PHONY : bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.requires

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.provides: bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.requires
	$(MAKE) -f bingchen/base/tests/CMakeFiles/Thread_unittest.dir/build.make bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.provides.build
.PHONY : bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.provides

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.provides.build: bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o

# Object files for target Thread_unittest
Thread_unittest_OBJECTS = \
"CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o"

# External object files for target Thread_unittest
Thread_unittest_EXTERNAL_OBJECTS =

bin/Thread_unittest: bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o
bin/Thread_unittest: bingchen/base/tests/CMakeFiles/Thread_unittest.dir/build.make
bin/Thread_unittest: lib/libbingchen_base.a
bin/Thread_unittest: bingchen/base/tests/CMakeFiles/Thread_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/Thread_unittest"
	cd /root/code/bingchen/build/bingchen/base/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Thread_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bingchen/base/tests/CMakeFiles/Thread_unittest.dir/build: bin/Thread_unittest
.PHONY : bingchen/base/tests/CMakeFiles/Thread_unittest.dir/build

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/requires: bingchen/base/tests/CMakeFiles/Thread_unittest.dir/Thread_unittest.cc.o.requires
.PHONY : bingchen/base/tests/CMakeFiles/Thread_unittest.dir/requires

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/clean:
	cd /root/code/bingchen/build/bingchen/base/tests && $(CMAKE_COMMAND) -P CMakeFiles/Thread_unittest.dir/cmake_clean.cmake
.PHONY : bingchen/base/tests/CMakeFiles/Thread_unittest.dir/clean

bingchen/base/tests/CMakeFiles/Thread_unittest.dir/depend:
	cd /root/code/bingchen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/code/bingchen /root/code/bingchen/bingchen/base/tests /root/code/bingchen/build /root/code/bingchen/build/bingchen/base/tests /root/code/bingchen/build/bingchen/base/tests/CMakeFiles/Thread_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bingchen/base/tests/CMakeFiles/Thread_unittest.dir/depend

