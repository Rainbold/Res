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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lyte/Documents/Projets/re216/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lyte/Documents/Projets/re216/build

# Include any dependencies generated for this target.
include jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/depend.make

# Include the progress variables for this target.
include jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/progress.make

# Include the compile flags for this target's objects.
include jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/flags.make

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/flags.make
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o: /home/lyte/Documents/Projets/re216/src/jalon02/client/client.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lyte/Documents/Projets/re216/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o   -c /home/lyte/Documents/Projets/re216/src/jalon02/client/client.c

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.i"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/lyte/Documents/Projets/re216/src/jalon02/client/client.c > CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.i

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.s"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/lyte/Documents/Projets/re216/src/jalon02/client/client.c -o CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.s

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.requires:
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.requires

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.provides: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.requires
	$(MAKE) -f jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/build.make jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.provides.build
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.provides

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.provides.build: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/flags.make
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o: /home/lyte/Documents/Projets/re216/src/jalon02/client/client_lib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lyte/Documents/Projets/re216/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o   -c /home/lyte/Documents/Projets/re216/src/jalon02/client/client_lib.c

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.i"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/lyte/Documents/Projets/re216/src/jalon02/client/client_lib.c > CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.i

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.s"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/lyte/Documents/Projets/re216/src/jalon02/client/client_lib.c -o CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.s

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.requires:
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.requires

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.provides: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.requires
	$(MAKE) -f jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/build.make jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.provides.build
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.provides

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.provides.build: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/flags.make
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o: /home/lyte/Documents/Projets/re216/src/jalon02/commons/network.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lyte/Documents/Projets/re216/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o   -c /home/lyte/Documents/Projets/re216/src/jalon02/commons/network.c

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.i"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/lyte/Documents/Projets/re216/src/jalon02/commons/network.c > CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.i

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.s"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/lyte/Documents/Projets/re216/src/jalon02/commons/network.c -o CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.s

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.requires:
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.requires

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.provides: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.requires
	$(MAKE) -f jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/build.make jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.provides.build
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.provides

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.provides.build: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/flags.make
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o: /home/lyte/Documents/Projets/re216/src/jalon02/commons/contrib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lyte/Documents/Projets/re216/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o   -c /home/lyte/Documents/Projets/re216/src/jalon02/commons/contrib.c

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.i"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/lyte/Documents/Projets/re216/src/jalon02/commons/contrib.c > CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.i

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.s"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/lyte/Documents/Projets/re216/src/jalon02/commons/contrib.c -o CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.s

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.requires:
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.requires

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.provides: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.requires
	$(MAKE) -f jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/build.make jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.provides.build
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.provides

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.provides.build: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o

# Object files for target RE216_JALON02_CLIENT
RE216_JALON02_CLIENT_OBJECTS = \
"CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o" \
"CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o" \
"CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o" \
"CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o"

# External object files for target RE216_JALON02_CLIENT
RE216_JALON02_CLIENT_EXTERNAL_OBJECTS =

jalon02/RE216_JALON02_CLIENT: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o
jalon02/RE216_JALON02_CLIENT: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o
jalon02/RE216_JALON02_CLIENT: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o
jalon02/RE216_JALON02_CLIENT: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o
jalon02/RE216_JALON02_CLIENT: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/build.make
jalon02/RE216_JALON02_CLIENT: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable RE216_JALON02_CLIENT"
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RE216_JALON02_CLIENT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/build: jalon02/RE216_JALON02_CLIENT
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/build

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/requires: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client.c.o.requires
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/requires: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/client/client_lib.c.o.requires
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/requires: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/network.c.o.requires
jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/requires: jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/commons/contrib.c.o.requires
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/requires

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/clean:
	cd /home/lyte/Documents/Projets/re216/build/jalon02 && $(CMAKE_COMMAND) -P CMakeFiles/RE216_JALON02_CLIENT.dir/cmake_clean.cmake
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/clean

jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/depend:
	cd /home/lyte/Documents/Projets/re216/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lyte/Documents/Projets/re216/src /home/lyte/Documents/Projets/re216/src/jalon02 /home/lyte/Documents/Projets/re216/build /home/lyte/Documents/Projets/re216/build/jalon02 /home/lyte/Documents/Projets/re216/build/jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jalon02/CMakeFiles/RE216_JALON02_CLIENT.dir/depend

