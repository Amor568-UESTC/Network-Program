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
CMAKE_SOURCE_DIR = /home/amor568/桌面/cpp/网络编程/SocketIPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amor568/桌面/cpp/网络编程/SocketIPC/build

# Include any dependencies generated for this target.
include CMakeFiles/domain_socket.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/domain_socket.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/domain_socket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/domain_socket.dir/flags.make

CMakeFiles/domain_socket.dir/domain_socket.cpp.o: CMakeFiles/domain_socket.dir/flags.make
CMakeFiles/domain_socket.dir/domain_socket.cpp.o: /home/amor568/桌面/cpp/网络编程/SocketIPC/domain_socket.cpp
CMakeFiles/domain_socket.dir/domain_socket.cpp.o: CMakeFiles/domain_socket.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amor568/桌面/cpp/网络编程/SocketIPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/domain_socket.dir/domain_socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/domain_socket.dir/domain_socket.cpp.o -MF CMakeFiles/domain_socket.dir/domain_socket.cpp.o.d -o CMakeFiles/domain_socket.dir/domain_socket.cpp.o -c /home/amor568/桌面/cpp/网络编程/SocketIPC/domain_socket.cpp

CMakeFiles/domain_socket.dir/domain_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/domain_socket.dir/domain_socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amor568/桌面/cpp/网络编程/SocketIPC/domain_socket.cpp > CMakeFiles/domain_socket.dir/domain_socket.cpp.i

CMakeFiles/domain_socket.dir/domain_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/domain_socket.dir/domain_socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amor568/桌面/cpp/网络编程/SocketIPC/domain_socket.cpp -o CMakeFiles/domain_socket.dir/domain_socket.cpp.s

CMakeFiles/domain_socket.dir/wrap.cpp.o: CMakeFiles/domain_socket.dir/flags.make
CMakeFiles/domain_socket.dir/wrap.cpp.o: /home/amor568/桌面/cpp/网络编程/SocketIPC/wrap.cpp
CMakeFiles/domain_socket.dir/wrap.cpp.o: CMakeFiles/domain_socket.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/amor568/桌面/cpp/网络编程/SocketIPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/domain_socket.dir/wrap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/domain_socket.dir/wrap.cpp.o -MF CMakeFiles/domain_socket.dir/wrap.cpp.o.d -o CMakeFiles/domain_socket.dir/wrap.cpp.o -c /home/amor568/桌面/cpp/网络编程/SocketIPC/wrap.cpp

CMakeFiles/domain_socket.dir/wrap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/domain_socket.dir/wrap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amor568/桌面/cpp/网络编程/SocketIPC/wrap.cpp > CMakeFiles/domain_socket.dir/wrap.cpp.i

CMakeFiles/domain_socket.dir/wrap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/domain_socket.dir/wrap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amor568/桌面/cpp/网络编程/SocketIPC/wrap.cpp -o CMakeFiles/domain_socket.dir/wrap.cpp.s

# Object files for target domain_socket
domain_socket_OBJECTS = \
"CMakeFiles/domain_socket.dir/domain_socket.cpp.o" \
"CMakeFiles/domain_socket.dir/wrap.cpp.o"

# External object files for target domain_socket
domain_socket_EXTERNAL_OBJECTS =

domain_socket: CMakeFiles/domain_socket.dir/domain_socket.cpp.o
domain_socket: CMakeFiles/domain_socket.dir/wrap.cpp.o
domain_socket: CMakeFiles/domain_socket.dir/build.make
domain_socket: CMakeFiles/domain_socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/amor568/桌面/cpp/网络编程/SocketIPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable domain_socket"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/domain_socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/domain_socket.dir/build: domain_socket
.PHONY : CMakeFiles/domain_socket.dir/build

CMakeFiles/domain_socket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/domain_socket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/domain_socket.dir/clean

CMakeFiles/domain_socket.dir/depend:
	cd /home/amor568/桌面/cpp/网络编程/SocketIPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amor568/桌面/cpp/网络编程/SocketIPC /home/amor568/桌面/cpp/网络编程/SocketIPC /home/amor568/桌面/cpp/网络编程/SocketIPC/build /home/amor568/桌面/cpp/网络编程/SocketIPC/build /home/amor568/桌面/cpp/网络编程/SocketIPC/build/CMakeFiles/domain_socket.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/domain_socket.dir/depend

