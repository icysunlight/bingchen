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
include bingchen/base/CMakeFiles/bingchen_base.dir/depend.make

# Include the progress variables for this target.
include bingchen/base/CMakeFiles/bingchen_base.dir/progress.make

# Include the compile flags for this target's objects.
include bingchen/base/CMakeFiles/bingchen_base.dir/flags.make

bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o: bingchen/base/CMakeFiles/bingchen_base.dir/flags.make
bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o: ../bingchen/base/Exception.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/code/bingchen/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o"
	cd /root/code/bingchen/build/bingchen/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bingchen_base.dir/Exception.cc.o -c /root/code/bingchen/bingchen/base/Exception.cc

bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bingchen_base.dir/Exception.cc.i"
	cd /root/code/bingchen/build/bingchen/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/code/bingchen/bingchen/base/Exception.cc > CMakeFiles/bingchen_base.dir/Exception.cc.i

bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bingchen_base.dir/Exception.cc.s"
	cd /root/code/bingchen/build/bingchen/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/code/bingchen/bingchen/base/Exception.cc -o CMakeFiles/bingchen_base.dir/Exception.cc.s

bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.requires:
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.requires

bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.provides: bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.requires
	$(MAKE) -f bingchen/base/CMakeFiles/bingchen_base.dir/build.make bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.provides.build
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.provides

bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.provides.build: bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o

bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o: bingchen/base/CMakeFiles/bingchen_base.dir/flags.make
bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o: ../bingchen/base/TimeStamp.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/code/bingchen/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o"
	cd /root/code/bingchen/build/bingchen/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bingchen_base.dir/TimeStamp.cc.o -c /root/code/bingchen/bingchen/base/TimeStamp.cc

bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bingchen_base.dir/TimeStamp.cc.i"
	cd /root/code/bingchen/build/bingchen/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/code/bingchen/bingchen/base/TimeStamp.cc > CMakeFiles/bingchen_base.dir/TimeStamp.cc.i

bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bingchen_base.dir/TimeStamp.cc.s"
	cd /root/code/bingchen/build/bingchen/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/code/bingchen/bingchen/base/TimeStamp.cc -o CMakeFiles/bingchen_base.dir/TimeStamp.cc.s

bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.requires:
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.requires

bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.provides: bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.requires
	$(MAKE) -f bingchen/base/CMakeFiles/bingchen_base.dir/build.make bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.provides.build
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.provides

bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.provides.build: bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o

bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o: bingchen/base/CMakeFiles/bingchen_base.dir/flags.make
bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o: ../bingchen/base/Thread.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /root/code/bingchen/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o"
	cd /root/code/bingchen/build/bingchen/base && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bingchen_base.dir/Thread.cc.o -c /root/code/bingchen/bingchen/base/Thread.cc

bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bingchen_base.dir/Thread.cc.i"
	cd /root/code/bingchen/build/bingchen/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/code/bingchen/bingchen/base/Thread.cc > CMakeFiles/bingchen_base.dir/Thread.cc.i

bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bingchen_base.dir/Thread.cc.s"
	cd /root/code/bingchen/build/bingchen/base && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/code/bingchen/bingchen/base/Thread.cc -o CMakeFiles/bingchen_base.dir/Thread.cc.s

bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.requires:
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.requires

bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.provides: bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.requires
	$(MAKE) -f bingchen/base/CMakeFiles/bingchen_base.dir/build.make bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.provides.build
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.provides

bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.provides.build: bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o

# Object files for target bingchen_base
bingchen_base_OBJECTS = \
"CMakeFiles/bingchen_base.dir/Exception.cc.o" \
"CMakeFiles/bingchen_base.dir/TimeStamp.cc.o" \
"CMakeFiles/bingchen_base.dir/Thread.cc.o"

# External object files for target bingchen_base
bingchen_base_EXTERNAL_OBJECTS =

lib/libbingchen_base.a: bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o
lib/libbingchen_base.a: bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o
lib/libbingchen_base.a: bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o
lib/libbingchen_base.a: bingchen/base/CMakeFiles/bingchen_base.dir/build.make
lib/libbingchen_base.a: bingchen/base/CMakeFiles/bingchen_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libbingchen_base.a"
	cd /root/code/bingchen/build/bingchen/base && $(CMAKE_COMMAND) -P CMakeFiles/bingchen_base.dir/cmake_clean_target.cmake
	cd /root/code/bingchen/build/bingchen/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bingchen_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bingchen/base/CMakeFiles/bingchen_base.dir/build: lib/libbingchen_base.a
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/build

bingchen/base/CMakeFiles/bingchen_base.dir/requires: bingchen/base/CMakeFiles/bingchen_base.dir/Exception.cc.o.requires
bingchen/base/CMakeFiles/bingchen_base.dir/requires: bingchen/base/CMakeFiles/bingchen_base.dir/TimeStamp.cc.o.requires
bingchen/base/CMakeFiles/bingchen_base.dir/requires: bingchen/base/CMakeFiles/bingchen_base.dir/Thread.cc.o.requires
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/requires

bingchen/base/CMakeFiles/bingchen_base.dir/clean:
	cd /root/code/bingchen/build/bingchen/base && $(CMAKE_COMMAND) -P CMakeFiles/bingchen_base.dir/cmake_clean.cmake
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/clean

bingchen/base/CMakeFiles/bingchen_base.dir/depend:
	cd /root/code/bingchen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/code/bingchen /root/code/bingchen/bingchen/base /root/code/bingchen/build /root/code/bingchen/build/bingchen/base /root/code/bingchen/build/bingchen/base/CMakeFiles/bingchen_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bingchen/base/CMakeFiles/bingchen_base.dir/depend

