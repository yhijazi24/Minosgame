# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/kamir/Téléchargements/Minosgame-main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kamir/Téléchargements/Minosgame-main

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kamir/Téléchargements/Minosgame-main/CMakeFiles /home/kamir/Téléchargements/Minosgame-main/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kamir/Téléchargements/Minosgame-main/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Minosgames

# Build rule for target.
Minosgames: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Minosgames
.PHONY : Minosgames

# fast build rule for target.
Minosgames/fast:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/build
.PHONY : Minosgames/fast

dominos/dominos_events.o: dominos/dominos_events.c.o

.PHONY : dominos/dominos_events.o

# target to build an object file
dominos/dominos_events.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_events.c.o
.PHONY : dominos/dominos_events.c.o

dominos/dominos_events.i: dominos/dominos_events.c.i

.PHONY : dominos/dominos_events.i

# target to preprocess a source file
dominos/dominos_events.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_events.c.i
.PHONY : dominos/dominos_events.c.i

dominos/dominos_events.s: dominos/dominos_events.c.s

.PHONY : dominos/dominos_events.s

# target to generate assembly for a file
dominos/dominos_events.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_events.c.s
.PHONY : dominos/dominos_events.c.s

dominos/dominos_game.o: dominos/dominos_game.c.o

.PHONY : dominos/dominos_game.o

# target to build an object file
dominos/dominos_game.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_game.c.o
.PHONY : dominos/dominos_game.c.o

dominos/dominos_game.i: dominos/dominos_game.c.i

.PHONY : dominos/dominos_game.i

# target to preprocess a source file
dominos/dominos_game.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_game.c.i
.PHONY : dominos/dominos_game.c.i

dominos/dominos_game.s: dominos/dominos_game.c.s

.PHONY : dominos/dominos_game.s

# target to generate assembly for a file
dominos/dominos_game.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_game.c.s
.PHONY : dominos/dominos_game.c.s

dominos/dominos_renderer.o: dominos/dominos_renderer.c.o

.PHONY : dominos/dominos_renderer.o

# target to build an object file
dominos/dominos_renderer.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_renderer.c.o
.PHONY : dominos/dominos_renderer.c.o

dominos/dominos_renderer.i: dominos/dominos_renderer.c.i

.PHONY : dominos/dominos_renderer.i

# target to preprocess a source file
dominos/dominos_renderer.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_renderer.c.i
.PHONY : dominos/dominos_renderer.c.i

dominos/dominos_renderer.s: dominos/dominos_renderer.c.s

.PHONY : dominos/dominos_renderer.s

# target to generate assembly for a file
dominos/dominos_renderer.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_renderer.c.s
.PHONY : dominos/dominos_renderer.c.s

dominos/dominos_types.o: dominos/dominos_types.c.o

.PHONY : dominos/dominos_types.o

# target to build an object file
dominos/dominos_types.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_types.c.o
.PHONY : dominos/dominos_types.c.o

dominos/dominos_types.i: dominos/dominos_types.c.i

.PHONY : dominos/dominos_types.i

# target to preprocess a source file
dominos/dominos_types.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_types.c.i
.PHONY : dominos/dominos_types.c.i

dominos/dominos_types.s: dominos/dominos_types.c.s

.PHONY : dominos/dominos_types.s

# target to generate assembly for a file
dominos/dominos_types.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/dominos/dominos_types.c.s
.PHONY : dominos/dominos_types.c.s

game.o: game.c.o

.PHONY : game.o

# target to build an object file
game.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/game.c.o
.PHONY : game.c.o

game.i: game.c.i

.PHONY : game.i

# target to preprocess a source file
game.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/game.c.i
.PHONY : game.c.i

game.s: game.c.s

.PHONY : game.s

# target to generate assembly for a file
game.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/game.c.s
.PHONY : game.c.s

game_score.o: game_score.c.o

.PHONY : game_score.o

# target to build an object file
game_score.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/game_score.c.o
.PHONY : game_score.c.o

game_score.i: game_score.c.i

.PHONY : game_score.i

# target to preprocess a source file
game_score.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/game_score.c.i
.PHONY : game_score.c.i

game_score.s: game_score.c.s

.PHONY : game_score.s

# target to generate assembly for a file
game_score.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/game_score.c.s
.PHONY : game_score.c.s

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/main.c.s
.PHONY : main.c.s

menu.o: menu.c.o

.PHONY : menu.o

# target to build an object file
menu.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/menu.c.o
.PHONY : menu.c.o

menu.i: menu.c.i

.PHONY : menu.i

# target to preprocess a source file
menu.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/menu.c.i
.PHONY : menu.c.i

menu.s: menu.c.s

.PHONY : menu.s

# target to generate assembly for a file
menu.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/menu.c.s
.PHONY : menu.c.s

player_setup.o: player_setup.c.o

.PHONY : player_setup.o

# target to build an object file
player_setup.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/player_setup.c.o
.PHONY : player_setup.c.o

player_setup.i: player_setup.c.i

.PHONY : player_setup.i

# target to preprocess a source file
player_setup.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/player_setup.c.i
.PHONY : player_setup.c.i

player_setup.s: player_setup.c.s

.PHONY : player_setup.s

# target to generate assembly for a file
player_setup.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/player_setup.c.s
.PHONY : player_setup.c.s

triominos/triomino_events.o: triominos/triomino_events.c.o

.PHONY : triominos/triomino_events.o

# target to build an object file
triominos/triomino_events.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_events.c.o
.PHONY : triominos/triomino_events.c.o

triominos/triomino_events.i: triominos/triomino_events.c.i

.PHONY : triominos/triomino_events.i

# target to preprocess a source file
triominos/triomino_events.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_events.c.i
.PHONY : triominos/triomino_events.c.i

triominos/triomino_events.s: triominos/triomino_events.c.s

.PHONY : triominos/triomino_events.s

# target to generate assembly for a file
triominos/triomino_events.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_events.c.s
.PHONY : triominos/triomino_events.c.s

triominos/triomino_game.o: triominos/triomino_game.c.o

.PHONY : triominos/triomino_game.o

# target to build an object file
triominos/triomino_game.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_game.c.o
.PHONY : triominos/triomino_game.c.o

triominos/triomino_game.i: triominos/triomino_game.c.i

.PHONY : triominos/triomino_game.i

# target to preprocess a source file
triominos/triomino_game.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_game.c.i
.PHONY : triominos/triomino_game.c.i

triominos/triomino_game.s: triominos/triomino_game.c.s

.PHONY : triominos/triomino_game.s

# target to generate assembly for a file
triominos/triomino_game.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_game.c.s
.PHONY : triominos/triomino_game.c.s

triominos/triomino_renderer.o: triominos/triomino_renderer.c.o

.PHONY : triominos/triomino_renderer.o

# target to build an object file
triominos/triomino_renderer.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_renderer.c.o
.PHONY : triominos/triomino_renderer.c.o

triominos/triomino_renderer.i: triominos/triomino_renderer.c.i

.PHONY : triominos/triomino_renderer.i

# target to preprocess a source file
triominos/triomino_renderer.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_renderer.c.i
.PHONY : triominos/triomino_renderer.c.i

triominos/triomino_renderer.s: triominos/triomino_renderer.c.s

.PHONY : triominos/triomino_renderer.s

# target to generate assembly for a file
triominos/triomino_renderer.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_renderer.c.s
.PHONY : triominos/triomino_renderer.c.s

triominos/triomino_types.o: triominos/triomino_types.c.o

.PHONY : triominos/triomino_types.o

# target to build an object file
triominos/triomino_types.c.o:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_types.c.o
.PHONY : triominos/triomino_types.c.o

triominos/triomino_types.i: triominos/triomino_types.c.i

.PHONY : triominos/triomino_types.i

# target to preprocess a source file
triominos/triomino_types.c.i:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_types.c.i
.PHONY : triominos/triomino_types.c.i

triominos/triomino_types.s: triominos/triomino_types.c.s

.PHONY : triominos/triomino_types.s

# target to generate assembly for a file
triominos/triomino_types.c.s:
	$(MAKE) -f CMakeFiles/Minosgames.dir/build.make CMakeFiles/Minosgames.dir/triominos/triomino_types.c.s
.PHONY : triominos/triomino_types.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... Minosgames"
	@echo "... dominos/dominos_events.o"
	@echo "... dominos/dominos_events.i"
	@echo "... dominos/dominos_events.s"
	@echo "... dominos/dominos_game.o"
	@echo "... dominos/dominos_game.i"
	@echo "... dominos/dominos_game.s"
	@echo "... dominos/dominos_renderer.o"
	@echo "... dominos/dominos_renderer.i"
	@echo "... dominos/dominos_renderer.s"
	@echo "... dominos/dominos_types.o"
	@echo "... dominos/dominos_types.i"
	@echo "... dominos/dominos_types.s"
	@echo "... game.o"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... game_score.o"
	@echo "... game_score.i"
	@echo "... game_score.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... menu.o"
	@echo "... menu.i"
	@echo "... menu.s"
	@echo "... player_setup.o"
	@echo "... player_setup.i"
	@echo "... player_setup.s"
	@echo "... triominos/triomino_events.o"
	@echo "... triominos/triomino_events.i"
	@echo "... triominos/triomino_events.s"
	@echo "... triominos/triomino_game.o"
	@echo "... triominos/triomino_game.i"
	@echo "... triominos/triomino_game.s"
	@echo "... triominos/triomino_renderer.o"
	@echo "... triominos/triomino_renderer.i"
	@echo "... triominos/triomino_renderer.s"
	@echo "... triominos/triomino_types.o"
	@echo "... triominos/triomino_types.i"
	@echo "... triominos/triomino_types.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

