# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amor568/桌面/cpp/网络编程/pollServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amor568/桌面/cpp/网络编程/pollServer/build

# Include any dependencies generated for this target.
include CMakeFiles/pollServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pollServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pollServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pollServer.dir/flags.make

CMakeFiles/pollServer.dir/pollServer.cpp.o: CMakeFiles/pollServer.dir/flags.make
CMakeFiles/pollServer.dir/pollServer.cpp.o: /home/amor568/桌面/cpp/网络编程/pollServer/pollServer.cpp
CMakeFiles/pollServer.dir/pollServer.cpp.o: CMakeFiles/pollServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amor568/桌面/cpp/网络编程/pollServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pollServer.dir/pollServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pollServer.dir/pollServer.cpp.o -MF CMakeFiles/pollServer.dir/pollServer.cpp.o.d -o CMakeFiles/pollServer.dir/pollServer.cpp.o -c /home/amor568/桌面/cpp/网络编程/pollServer/pollServer.cpp

CMakeFiles/pollServer.dir/pollServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pollServer.dir/pollServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amor568/桌面/cpp/网络编程/pollServer/pollServer.cpp > CMakeFiles/pollServer.dir/pollServer.cpp.i

CMakeFiles/pollServer.dir/pollServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pollServer.dir/pollServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amor568/桌面/cpp/网络编程/pollServer/pollServer.cpp -o CMakeFiles/pollServer.dir/pollServer.cpp.s

CMakeFiles/pollServer.dir/wrap.cpp.o: CMakeFiles/pollServer.dir/flags.make
CMakeFiles/pollServer.dir/wrap.cpp.o: /home/amor568/桌面/cpp/网络编程/pollServer/wrap.cpp
CMakeFiles/pollServer.dir/wrap.cpp.o: CMakeFiles/pollServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amor568/桌面/cpp/网络编程/pollServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pollServer.dir/wrap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pollServer.dir/wrap.cpp.o -MF CMakeFiles/pollServer.dir/wrap.cpp.o.d -o CMakeFiles/pollServer.dir/wrap.cpp.o -c /home/amor568/桌面/cpp/网络编程/pollServer/wrap.cpp

CMakeFiles/pollServer.dir/wrap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pollServer.dir/wrap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amor568/桌面/cpp/网络编程/pollServer/wrap.cpp > CMakeFiles/pollServer.dir/wrap.cpp.i

CMakeFiles/pollServer.dir/wrap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pollServer.dir/wrap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amor568/桌面/cpp/网络编程/pollServer/wrap.cpp -o CMakeFiles/pollServer.dir/wrap.cpp.s

# Object files for target pollServer
pollServer_OBJECTS = \
"CMakeFiles/pollServer.dir/pollServer.cpp.o" \
"CMakeFiles/pollServer.dir/wrap.cpp.o"

# External object files for target pollServer
pollServer_EXTERNAL_OBJECTS =

pollServer: CMakeFiles/pollServer.dir/pollServer.cpp.o
pollServer: CMakeFiles/pollServer.dir/wrap.cpp.o
pollServer: CMakeFiles/pollServer.dir/build.make
pollServer: CMakeFiles/pollServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/amor568/桌面/cpp/网络编程/pollServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable pollServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pollServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pollServer.dir/build: pollServer
.PHONY : CMakeFiles/pollServer.dir/build

CMakeFiles/pollServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pollServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pollServer.dir/clean

CMakeFiles/pollServer.dir/depend:
	cd /home/amor568/桌面/cpp/网络编程/pollServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amor568/桌面/cpp/网络编程/pollServer /home/amor568/桌面/cpp/网络编程/pollServer /home/amor568/桌面/cpp/网络编程/pollServer/build /home/amor568/桌面/cpp/网络编程/pollServer/build /home/amor568/桌面/cpp/网络编程/pollServer/build/CMakeFiles/pollServer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/pollServer.dir/depend

