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
CMAKE_SOURCE_DIR = /home/amor568/桌面/cpp/网络编程/epollheap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amor568/桌面/cpp/网络编程/epollheap/build

# Include any dependencies generated for this target.
include CMakeFiles/epollheap.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/epollheap.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/epollheap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/epollheap.dir/flags.make

CMakeFiles/epollheap.dir/epollheap.cpp.o: CMakeFiles/epollheap.dir/flags.make
CMakeFiles/epollheap.dir/epollheap.cpp.o: /home/amor568/桌面/cpp/网络编程/epollheap/epollheap.cpp
CMakeFiles/epollheap.dir/epollheap.cpp.o: CMakeFiles/epollheap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amor568/桌面/cpp/网络编程/epollheap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/epollheap.dir/epollheap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/epollheap.dir/epollheap.cpp.o -MF CMakeFiles/epollheap.dir/epollheap.cpp.o.d -o CMakeFiles/epollheap.dir/epollheap.cpp.o -c /home/amor568/桌面/cpp/网络编程/epollheap/epollheap.cpp

CMakeFiles/epollheap.dir/epollheap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/epollheap.dir/epollheap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amor568/桌面/cpp/网络编程/epollheap/epollheap.cpp > CMakeFiles/epollheap.dir/epollheap.cpp.i

CMakeFiles/epollheap.dir/epollheap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/epollheap.dir/epollheap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amor568/桌面/cpp/网络编程/epollheap/epollheap.cpp -o CMakeFiles/epollheap.dir/epollheap.cpp.s

CMakeFiles/epollheap.dir/wrap.cpp.o: CMakeFiles/epollheap.dir/flags.make
CMakeFiles/epollheap.dir/wrap.cpp.o: /home/amor568/桌面/cpp/网络编程/epollheap/wrap.cpp
CMakeFiles/epollheap.dir/wrap.cpp.o: CMakeFiles/epollheap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amor568/桌面/cpp/网络编程/epollheap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/epollheap.dir/wrap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/epollheap.dir/wrap.cpp.o -MF CMakeFiles/epollheap.dir/wrap.cpp.o.d -o CMakeFiles/epollheap.dir/wrap.cpp.o -c /home/amor568/桌面/cpp/网络编程/epollheap/wrap.cpp

CMakeFiles/epollheap.dir/wrap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/epollheap.dir/wrap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amor568/桌面/cpp/网络编程/epollheap/wrap.cpp > CMakeFiles/epollheap.dir/wrap.cpp.i

CMakeFiles/epollheap.dir/wrap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/epollheap.dir/wrap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amor568/桌面/cpp/网络编程/epollheap/wrap.cpp -o CMakeFiles/epollheap.dir/wrap.cpp.s

# Object files for target epollheap
epollheap_OBJECTS = \
"CMakeFiles/epollheap.dir/epollheap.cpp.o" \
"CMakeFiles/epollheap.dir/wrap.cpp.o"

# External object files for target epollheap
epollheap_EXTERNAL_OBJECTS =

epollheap: CMakeFiles/epollheap.dir/epollheap.cpp.o
epollheap: CMakeFiles/epollheap.dir/wrap.cpp.o
epollheap: CMakeFiles/epollheap.dir/build.make
epollheap: CMakeFiles/epollheap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/amor568/桌面/cpp/网络编程/epollheap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable epollheap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/epollheap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/epollheap.dir/build: epollheap
.PHONY : CMakeFiles/epollheap.dir/build

CMakeFiles/epollheap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/epollheap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/epollheap.dir/clean

CMakeFiles/epollheap.dir/depend:
	cd /home/amor568/桌面/cpp/网络编程/epollheap/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amor568/桌面/cpp/网络编程/epollheap /home/amor568/桌面/cpp/网络编程/epollheap /home/amor568/桌面/cpp/网络编程/epollheap/build /home/amor568/桌面/cpp/网络编程/epollheap/build /home/amor568/桌面/cpp/网络编程/epollheap/build/CMakeFiles/epollheap.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/epollheap.dir/depend

