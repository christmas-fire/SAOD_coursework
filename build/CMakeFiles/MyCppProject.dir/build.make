# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\christmas_fire\VScodeProjects\SAOD_coursework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build

# Include any dependencies generated for this target.
include CMakeFiles/MyCppProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyCppProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyCppProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyCppProject.dir/flags.make

CMakeFiles/MyCppProject.dir/codegen:
.PHONY : CMakeFiles/MyCppProject.dir/codegen

CMakeFiles/MyCppProject.dir/src/coding.cpp.obj: CMakeFiles/MyCppProject.dir/flags.make
CMakeFiles/MyCppProject.dir/src/coding.cpp.obj: C:/Users/christmas_fire/VScodeProjects/SAOD_coursework/src/coding.cpp
CMakeFiles/MyCppProject.dir/src/coding.cpp.obj: CMakeFiles/MyCppProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyCppProject.dir/src/coding.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyCppProject.dir/src/coding.cpp.obj -MF CMakeFiles\MyCppProject.dir\src\coding.cpp.obj.d -o CMakeFiles\MyCppProject.dir\src\coding.cpp.obj -c C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\coding.cpp

CMakeFiles/MyCppProject.dir/src/coding.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyCppProject.dir/src/coding.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\coding.cpp > CMakeFiles\MyCppProject.dir\src\coding.cpp.i

CMakeFiles/MyCppProject.dir/src/coding.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyCppProject.dir/src/coding.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\coding.cpp -o CMakeFiles\MyCppProject.dir\src\coding.cpp.s

CMakeFiles/MyCppProject.dir/src/list.cpp.obj: CMakeFiles/MyCppProject.dir/flags.make
CMakeFiles/MyCppProject.dir/src/list.cpp.obj: C:/Users/christmas_fire/VScodeProjects/SAOD_coursework/src/list.cpp
CMakeFiles/MyCppProject.dir/src/list.cpp.obj: CMakeFiles/MyCppProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyCppProject.dir/src/list.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyCppProject.dir/src/list.cpp.obj -MF CMakeFiles\MyCppProject.dir\src\list.cpp.obj.d -o CMakeFiles\MyCppProject.dir\src\list.cpp.obj -c C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\list.cpp

CMakeFiles/MyCppProject.dir/src/list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyCppProject.dir/src/list.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\list.cpp > CMakeFiles\MyCppProject.dir\src\list.cpp.i

CMakeFiles/MyCppProject.dir/src/list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyCppProject.dir/src/list.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\list.cpp -o CMakeFiles\MyCppProject.dir\src\list.cpp.s

CMakeFiles/MyCppProject.dir/src/output.cpp.obj: CMakeFiles/MyCppProject.dir/flags.make
CMakeFiles/MyCppProject.dir/src/output.cpp.obj: C:/Users/christmas_fire/VScodeProjects/SAOD_coursework/src/output.cpp
CMakeFiles/MyCppProject.dir/src/output.cpp.obj: CMakeFiles/MyCppProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyCppProject.dir/src/output.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyCppProject.dir/src/output.cpp.obj -MF CMakeFiles\MyCppProject.dir\src\output.cpp.obj.d -o CMakeFiles\MyCppProject.dir\src\output.cpp.obj -c C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\output.cpp

CMakeFiles/MyCppProject.dir/src/output.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyCppProject.dir/src/output.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\output.cpp > CMakeFiles\MyCppProject.dir\src\output.cpp.i

CMakeFiles/MyCppProject.dir/src/output.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyCppProject.dir/src/output.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\output.cpp -o CMakeFiles\MyCppProject.dir\src\output.cpp.s

CMakeFiles/MyCppProject.dir/src/test.cpp.obj: CMakeFiles/MyCppProject.dir/flags.make
CMakeFiles/MyCppProject.dir/src/test.cpp.obj: C:/Users/christmas_fire/VScodeProjects/SAOD_coursework/src/test.cpp
CMakeFiles/MyCppProject.dir/src/test.cpp.obj: CMakeFiles/MyCppProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyCppProject.dir/src/test.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyCppProject.dir/src/test.cpp.obj -MF CMakeFiles\MyCppProject.dir\src\test.cpp.obj.d -o CMakeFiles\MyCppProject.dir\src\test.cpp.obj -c C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\test.cpp

CMakeFiles/MyCppProject.dir/src/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyCppProject.dir/src/test.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\test.cpp > CMakeFiles\MyCppProject.dir\src\test.cpp.i

CMakeFiles/MyCppProject.dir/src/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyCppProject.dir/src/test.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\test.cpp -o CMakeFiles\MyCppProject.dir\src\test.cpp.s

CMakeFiles/MyCppProject.dir/src/tree.cpp.obj: CMakeFiles/MyCppProject.dir/flags.make
CMakeFiles/MyCppProject.dir/src/tree.cpp.obj: C:/Users/christmas_fire/VScodeProjects/SAOD_coursework/src/tree.cpp
CMakeFiles/MyCppProject.dir/src/tree.cpp.obj: CMakeFiles/MyCppProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MyCppProject.dir/src/tree.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyCppProject.dir/src/tree.cpp.obj -MF CMakeFiles\MyCppProject.dir\src\tree.cpp.obj.d -o CMakeFiles\MyCppProject.dir\src\tree.cpp.obj -c C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\tree.cpp

CMakeFiles/MyCppProject.dir/src/tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyCppProject.dir/src/tree.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\tree.cpp > CMakeFiles\MyCppProject.dir\src\tree.cpp.i

CMakeFiles/MyCppProject.dir/src/tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyCppProject.dir/src/tree.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\src\tree.cpp -o CMakeFiles\MyCppProject.dir\src\tree.cpp.s

# Object files for target MyCppProject
MyCppProject_OBJECTS = \
"CMakeFiles/MyCppProject.dir/src/coding.cpp.obj" \
"CMakeFiles/MyCppProject.dir/src/list.cpp.obj" \
"CMakeFiles/MyCppProject.dir/src/output.cpp.obj" \
"CMakeFiles/MyCppProject.dir/src/test.cpp.obj" \
"CMakeFiles/MyCppProject.dir/src/tree.cpp.obj"

# External object files for target MyCppProject
MyCppProject_EXTERNAL_OBJECTS =

MyCppProject.exe: CMakeFiles/MyCppProject.dir/src/coding.cpp.obj
MyCppProject.exe: CMakeFiles/MyCppProject.dir/src/list.cpp.obj
MyCppProject.exe: CMakeFiles/MyCppProject.dir/src/output.cpp.obj
MyCppProject.exe: CMakeFiles/MyCppProject.dir/src/test.cpp.obj
MyCppProject.exe: CMakeFiles/MyCppProject.dir/src/tree.cpp.obj
MyCppProject.exe: CMakeFiles/MyCppProject.dir/build.make
MyCppProject.exe: CMakeFiles/MyCppProject.dir/linkLibs.rsp
MyCppProject.exe: CMakeFiles/MyCppProject.dir/objects1.rsp
MyCppProject.exe: CMakeFiles/MyCppProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable MyCppProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MyCppProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyCppProject.dir/build: MyCppProject.exe
.PHONY : CMakeFiles/MyCppProject.dir/build

CMakeFiles/MyCppProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MyCppProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MyCppProject.dir/clean

CMakeFiles/MyCppProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\christmas_fire\VScodeProjects\SAOD_coursework C:\Users\christmas_fire\VScodeProjects\SAOD_coursework C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build C:\Users\christmas_fire\VScodeProjects\SAOD_coursework\build\CMakeFiles\MyCppProject.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyCppProject.dir/depend
