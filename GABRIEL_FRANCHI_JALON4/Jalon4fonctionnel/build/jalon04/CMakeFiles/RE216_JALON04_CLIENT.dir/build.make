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
CMAKE_SOURCE_DIR = /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build

# Include any dependencies generated for this target.
include jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/depend.make

# Include the progress variables for this target.
include jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/progress.make

# Include the compile flags for this target's objects.
include jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/flags.make

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/flags.make
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o: /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/client.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o   -c /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/client.c

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.i"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/client.c > CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.i

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.s"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/client.c -o CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.s

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.requires:
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.requires

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.provides: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.requires
	$(MAKE) -f jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/build.make jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.provides.build
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.provides

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.provides.build: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/flags.make
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o: /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/user.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o   -c /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/user.c

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.i"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/user.c > CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.i

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.s"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/user.c -o CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.s

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.requires:
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.requires

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.provides: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.requires
	$(MAKE) -f jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/build.make jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.provides.build
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.provides

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.provides.build: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/flags.make
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o: /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/fonction.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o   -c /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/fonction.c

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.i"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/fonction.c > CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.i

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.s"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/fonction.c -o CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.s

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.requires:
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.requires

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.provides: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.requires
	$(MAKE) -f jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/build.make jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.provides.build
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.provides

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.provides.build: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/flags.make
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o: /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/salon.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o   -c /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/salon.c

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.i"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/salon.c > CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.i

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.s"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04/salon.c -o CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.s

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.requires:
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.requires

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.provides: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.requires
	$(MAKE) -f jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/build.make jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.provides.build
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.provides

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.provides.build: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o

# Object files for target RE216_JALON04_CLIENT
RE216_JALON04_CLIENT_OBJECTS = \
"CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o" \
"CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o" \
"CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o" \
"CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o"

# External object files for target RE216_JALON04_CLIENT
RE216_JALON04_CLIENT_EXTERNAL_OBJECTS =

jalon04/RE216_JALON04_CLIENT: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o
jalon04/RE216_JALON04_CLIENT: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o
jalon04/RE216_JALON04_CLIENT: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o
jalon04/RE216_JALON04_CLIENT: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o
jalon04/RE216_JALON04_CLIENT: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/build.make
jalon04/RE216_JALON04_CLIENT: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable RE216_JALON04_CLIENT"
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RE216_JALON04_CLIENT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/build: jalon04/RE216_JALON04_CLIENT
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/build

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/requires: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/client.c.o.requires
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/requires: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/user.c.o.requires
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/requires: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/fonction.c.o.requires
jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/requires: jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/salon.c.o.requires
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/requires

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/clean:
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 && $(CMAKE_COMMAND) -P CMakeFiles/RE216_JALON04_CLIENT.dir/cmake_clean.cmake
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/clean

jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/depend:
	cd /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/src/jalon04 /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04 /home/ggabriel/S7/RE216/GABRIEL_FRANCHI_JALON4/Jalon4fonctionnel/build/jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jalon04/CMakeFiles/RE216_JALON04_CLIENT.dir/depend

