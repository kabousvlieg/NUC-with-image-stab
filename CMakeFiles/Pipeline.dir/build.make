# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/kobus/Kobus/clion_workspace/NUC-with-image-stab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kobus/Kobus/clion_workspace/NUC-with-image-stab

# Include any dependencies generated for this target.
include CMakeFiles/Pipeline.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Pipeline.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Pipeline.dir/flags.make

CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o: src/gui/gui_thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/gui/gui_thread.cpp

CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/gui/gui_thread.cpp > CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.i

CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/gui/gui_thread.cpp -o CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.s

CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.requires

CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.provides: CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.provides

CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o

CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o: src/gui/widgets.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/gui/widgets.cpp

CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/gui/widgets.cpp > CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.i

CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/gui/widgets.cpp -o CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.s

CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.requires

CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.provides: CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.provides

CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o

CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o: src/ti/ti_thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/ti/ti_thread.cpp

CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/ti/ti_thread.cpp > CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.i

CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/ti/ti_thread.cpp -o CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.s

CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.requires

CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.provides: CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.provides

CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o

CMakeFiles/Pipeline.dir/src/util/threads.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/util/threads.cpp.o: src/util/threads.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/util/threads.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/util/threads.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/util/threads.cpp

CMakeFiles/Pipeline.dir/src/util/threads.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/util/threads.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/util/threads.cpp > CMakeFiles/Pipeline.dir/src/util/threads.cpp.i

CMakeFiles/Pipeline.dir/src/util/threads.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/util/threads.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/util/threads.cpp -o CMakeFiles/Pipeline.dir/src/util/threads.cpp.s

CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.requires

CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.provides: CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.provides

CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/util/threads.cpp.o

CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o: src/util/timeClock.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/util/timeClock.cpp

CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/util/timeClock.cpp > CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.i

CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/util/timeClock.cpp -o CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.s

CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.requires

CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.provides: CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.provides

CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o

CMakeFiles/Pipeline.dir/src/main.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/main.cpp.o: src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/main.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/main.cpp

CMakeFiles/Pipeline.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/main.cpp > CMakeFiles/Pipeline.dir/src/main.cpp.i

CMakeFiles/Pipeline.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/main.cpp -o CMakeFiles/Pipeline.dir/src/main.cpp.s

CMakeFiles/Pipeline.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/main.cpp.o.requires

CMakeFiles/Pipeline.dir/src/main.cpp.o.provides: CMakeFiles/Pipeline.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/main.cpp.o.provides

CMakeFiles/Pipeline.dir/src/main.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/main.cpp.o

CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o: src/imageProcessing/cpuDsp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/cpuDsp.cpp

CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/cpuDsp.cpp > CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.i

CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/cpuDsp.cpp -o CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.s

CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.requires

CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.provides: CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.provides

CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o

CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o: src/imageProcessing/stabilisation.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/stabilisation.cpp

CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/stabilisation.cpp > CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.i

CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/stabilisation.cpp -o CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.s

CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.requires

CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.provides: CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.provides

CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o

CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o: src/imageProcessing/imageStabKalman.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/imageStabKalman.cpp

CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/imageStabKalman.cpp > CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.i

CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/imageProcessing/imageStabKalman.cpp -o CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.s

CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.requires

CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.provides: CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.provides

CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o

CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o: CMakeFiles/Pipeline.dir/flags.make
CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o: src/ti/camera.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o -c /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/ti/camera.cpp

CMakeFiles/Pipeline.dir/src/ti/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pipeline.dir/src/ti/camera.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/ti/camera.cpp > CMakeFiles/Pipeline.dir/src/ti/camera.cpp.i

CMakeFiles/Pipeline.dir/src/ti/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pipeline.dir/src/ti/camera.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/src/ti/camera.cpp -o CMakeFiles/Pipeline.dir/src/ti/camera.cpp.s

CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.requires:
.PHONY : CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.requires

CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.provides: CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pipeline.dir/build.make CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.provides.build
.PHONY : CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.provides

CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.provides.build: CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o

# Object files for target Pipeline
Pipeline_OBJECTS = \
"CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o" \
"CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o" \
"CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o" \
"CMakeFiles/Pipeline.dir/src/util/threads.cpp.o" \
"CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o" \
"CMakeFiles/Pipeline.dir/src/main.cpp.o" \
"CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o" \
"CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o" \
"CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o" \
"CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o"

# External object files for target Pipeline
Pipeline_EXTERNAL_OBJECTS =

Pipeline: CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/util/threads.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/main.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o
Pipeline: CMakeFiles/Pipeline.dir/build.make
Pipeline: /usr/lib/x86_64-linux-gnu/libboost_system.so
Pipeline: /usr/lib/x86_64-linux-gnu/libboost_thread.so
Pipeline: /usr/lib/x86_64-linux-gnu/libpthread.so
Pipeline: /usr/local/lib/libopencv_xphoto.so.3.1.0
Pipeline: /usr/local/lib/libopencv_xobjdetect.so.3.1.0
Pipeline: /usr/local/lib/libopencv_tracking.so.3.1.0
Pipeline: /usr/local/lib/libopencv_surface_matching.so.3.1.0
Pipeline: /usr/local/lib/libopencv_structured_light.so.3.1.0
Pipeline: /usr/local/lib/libopencv_stereo.so.3.1.0
Pipeline: /usr/local/lib/libopencv_saliency.so.3.1.0
Pipeline: /usr/local/lib/libopencv_rgbd.so.3.1.0
Pipeline: /usr/local/lib/libopencv_reg.so.3.1.0
Pipeline: /usr/local/lib/libopencv_plot.so.3.1.0
Pipeline: /usr/local/lib/libopencv_optflow.so.3.1.0
Pipeline: /usr/local/lib/libopencv_line_descriptor.so.3.1.0
Pipeline: /usr/local/lib/libopencv_fuzzy.so.3.1.0
Pipeline: /usr/local/lib/libopencv_dpm.so.3.1.0
Pipeline: /usr/local/lib/libopencv_dnn.so.3.1.0
Pipeline: /usr/local/lib/libopencv_datasets.so.3.1.0
Pipeline: /usr/local/lib/libopencv_ccalib.so.3.1.0
Pipeline: /usr/local/lib/libopencv_bioinspired.so.3.1.0
Pipeline: /usr/local/lib/libopencv_bgsegm.so.3.1.0
Pipeline: /usr/local/lib/libopencv_aruco.so.3.1.0
Pipeline: /usr/local/lib/libopencv_viz.so.3.1.0
Pipeline: /usr/local/lib/libopencv_videostab.so.3.1.0
Pipeline: /usr/local/lib/libopencv_superres.so.3.1.0
Pipeline: /usr/local/lib/libopencv_stitching.so.3.1.0
Pipeline: /usr/local/lib/libopencv_photo.so.3.1.0
Pipeline: /usr/lib/x86_64-linux-gnu/libSM.so
Pipeline: /usr/lib/x86_64-linux-gnu/libICE.so
Pipeline: /usr/lib/x86_64-linux-gnu/libX11.so
Pipeline: /usr/lib/x86_64-linux-gnu/libXext.so
Pipeline: /usr/local/lib/libopencv_text.so.3.1.0
Pipeline: /usr/local/lib/libopencv_face.so.3.1.0
Pipeline: /usr/local/lib/libopencv_ximgproc.so.3.1.0
Pipeline: /usr/local/lib/libopencv_xfeatures2d.so.3.1.0
Pipeline: /usr/local/lib/libopencv_shape.so.3.1.0
Pipeline: /usr/local/lib/libopencv_video.so.3.1.0
Pipeline: /usr/local/lib/libopencv_objdetect.so.3.1.0
Pipeline: /usr/local/lib/libopencv_calib3d.so.3.1.0
Pipeline: /usr/local/lib/libopencv_features2d.so.3.1.0
Pipeline: /usr/local/lib/libopencv_ml.so.3.1.0
Pipeline: /usr/local/lib/libopencv_highgui.so.3.1.0
Pipeline: /usr/local/lib/libopencv_videoio.so.3.1.0
Pipeline: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
Pipeline: /usr/local/lib/libopencv_imgproc.so.3.1.0
Pipeline: /usr/local/lib/libopencv_flann.so.3.1.0
Pipeline: /usr/local/lib/libopencv_core.so.3.1.0
Pipeline: CMakeFiles/Pipeline.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Pipeline"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Pipeline.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Pipeline.dir/build: Pipeline
.PHONY : CMakeFiles/Pipeline.dir/build

CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/gui/gui_thread.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/gui/widgets.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/ti/ti_thread.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/util/threads.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/util/timeClock.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/main.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/imageProcessing/cpuDsp.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/imageProcessing/stabilisation.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/imageProcessing/imageStabKalman.cpp.o.requires
CMakeFiles/Pipeline.dir/requires: CMakeFiles/Pipeline.dir/src/ti/camera.cpp.o.requires
.PHONY : CMakeFiles/Pipeline.dir/requires

CMakeFiles/Pipeline.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Pipeline.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Pipeline.dir/clean

CMakeFiles/Pipeline.dir/depend:
	cd /home/kobus/Kobus/clion_workspace/NUC-with-image-stab && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kobus/Kobus/clion_workspace/NUC-with-image-stab /home/kobus/Kobus/clion_workspace/NUC-with-image-stab /home/kobus/Kobus/clion_workspace/NUC-with-image-stab /home/kobus/Kobus/clion_workspace/NUC-with-image-stab /home/kobus/Kobus/clion_workspace/NUC-with-image-stab/CMakeFiles/Pipeline.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Pipeline.dir/depend
