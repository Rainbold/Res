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
CMAKE_SOURCE_DIR = /root/Enseirb/Res/jalon05/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Enseirb/Res/jalon05/build

# Include any dependencies generated for this target.
include jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/depend.make

# Include the progress variables for this target.
include jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/progress.make

# Include the compile flags for this target's objects.
include jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/flags.make

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/flags.make
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o: /root/Enseirb/Res/jalon05/src/jalon05/client/client.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/Enseirb/Res/jalon05/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o   -c /root/Enseirb/Res/jalon05/src/jalon05/client/client.c

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.i"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/Enseirb/Res/jalon05/src/jalon05/client/client.c > CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.i

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.s"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/Enseirb/Res/jalon05/src/jalon05/client/client.c -o CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.s

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.requires:
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.requires

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.provides: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.requires
	$(MAKE) -f jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/build.make jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.provides.build
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.provides

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.provides.build: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/flags.make
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o: /root/Enseirb/Res/jalon05/src/jalon05/client/client_lib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/Enseirb/Res/jalon05/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o   -c /root/Enseirb/Res/jalon05/src/jalon05/client/client_lib.c

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.i"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/Enseirb/Res/jalon05/src/jalon05/client/client_lib.c > CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.i

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.s"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/Enseirb/Res/jalon05/src/jalon05/client/client_lib.c -o CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.s

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.requires:
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.requires

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.provides: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.requires
	$(MAKE) -f jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/build.make jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.provides.build
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.provides

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.provides.build: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/flags.make
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o: /root/Enseirb/Res/jalon05/src/jalon05/commons/regex_lib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/Enseirb/Res/jalon05/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o   -c /root/Enseirb/Res/jalon05/src/jalon05/commons/regex_lib.c

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.i"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/Enseirb/Res/jalon05/src/jalon05/commons/regex_lib.c > CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.i

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.s"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/Enseirb/Res/jalon05/src/jalon05/commons/regex_lib.c -o CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.s

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.requires:
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.requires

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.provides: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.requires
	$(MAKE) -f jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/build.make jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.provides.build
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.provides

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.provides.build: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/flags.make
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o: /root/Enseirb/Res/jalon05/src/jalon05/commons/network.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/Enseirb/Res/jalon05/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o   -c /root/Enseirb/Res/jalon05/src/jalon05/commons/network.c

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.i"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/Enseirb/Res/jalon05/src/jalon05/commons/network.c > CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.i

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.s"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/Enseirb/Res/jalon05/src/jalon05/commons/network.c -o CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.s

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.requires:
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.requires

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.provides: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.requires
	$(MAKE) -f jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/build.make jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.provides.build
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.provides

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.provides.build: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o

# Object files for target RE216_JALON05_CLIENT
RE216_JALON05_CLIENT_OBJECTS = \
"CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o" \
"CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o" \
"CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o" \
"CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o"

# External object files for target RE216_JALON05_CLIENT
RE216_JALON05_CLIENT_EXTERNAL_OBJECTS =

jalon05/RE216_JALON05_CLIENT: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o
jalon05/RE216_JALON05_CLIENT: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o
jalon05/RE216_JALON05_CLIENT: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o
jalon05/RE216_JALON05_CLIENT: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o
jalon05/RE216_JALON05_CLIENT: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/build.make
jalon05/RE216_JALON05_CLIENT: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable RE216_JALON05_CLIENT"
	cd /root/Enseirb/Res/jalon05/build/jalon05 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RE216_JALON05_CLIENT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/build: jalon05/RE216_JALON05_CLIENT
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/build

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/requires: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client.c.o.requires
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/requires: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/client/client_lib.c.o.requires
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/requires: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/regex_lib.c.o.requires
jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/requires: jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/commons/network.c.o.requires
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/requires

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/clean:
	cd /root/Enseirb/Res/jalon05/build/jalon05 && $(CMAKE_COMMAND) -P CMakeFiles/RE216_JALON05_CLIENT.dir/cmake_clean.cmake
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/clean

jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/depend:
	cd /root/Enseirb/Res/jalon05/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Enseirb/Res/jalon05/src /root/Enseirb/Res/jalon05/src/jalon05 /root/Enseirb/Res/jalon05/build /root/Enseirb/Res/jalon05/build/jalon05 /root/Enseirb/Res/jalon05/build/jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jalon05/CMakeFiles/RE216_JALON05_CLIENT.dir/depend

