# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/yuuka/EMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuuka/EMP/build

# Include any dependencies generated for this target.
include main/CMakeFiles/EMP.dir/depend.make

# Include the progress variables for this target.
include main/CMakeFiles/EMP.dir/progress.make

# Include the compile flags for this target's objects.
include main/CMakeFiles/EMP.dir/flags.make

main/CMakeFiles/EMP.dir/main.cpp.o: main/CMakeFiles/EMP.dir/flags.make
main/CMakeFiles/EMP.dir/main.cpp.o: ../main/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuuka/EMP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object main/CMakeFiles/EMP.dir/main.cpp.o"
	cd /home/yuuka/EMP/build/main && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EMP.dir/main.cpp.o -c /home/yuuka/EMP/main/main.cpp

main/CMakeFiles/EMP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EMP.dir/main.cpp.i"
	cd /home/yuuka/EMP/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuuka/EMP/main/main.cpp > CMakeFiles/EMP.dir/main.cpp.i

main/CMakeFiles/EMP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EMP.dir/main.cpp.s"
	cd /home/yuuka/EMP/build/main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuuka/EMP/main/main.cpp -o CMakeFiles/EMP.dir/main.cpp.s

# Object files for target EMP
EMP_OBJECTS = \
"CMakeFiles/EMP.dir/main.cpp.o"

# External object files for target EMP
EMP_EXTERNAL_OBJECTS =

../EMP: main/CMakeFiles/EMP.dir/main.cpp.o
../EMP: main/CMakeFiles/EMP.dir/build.make
../EMP: src/libEMP_LIB.a
../EMP: main/CMakeFiles/EMP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuuka/EMP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../EMP"
	cd /home/yuuka/EMP/build/main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EMP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
main/CMakeFiles/EMP.dir/build: ../EMP

.PHONY : main/CMakeFiles/EMP.dir/build

main/CMakeFiles/EMP.dir/clean:
	cd /home/yuuka/EMP/build/main && $(CMAKE_COMMAND) -P CMakeFiles/EMP.dir/cmake_clean.cmake
.PHONY : main/CMakeFiles/EMP.dir/clean

main/CMakeFiles/EMP.dir/depend:
	cd /home/yuuka/EMP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuuka/EMP /home/yuuka/EMP/main /home/yuuka/EMP/build /home/yuuka/EMP/build/main /home/yuuka/EMP/build/main/CMakeFiles/EMP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : main/CMakeFiles/EMP.dir/depend

