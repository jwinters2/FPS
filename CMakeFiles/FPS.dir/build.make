# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/jamie/Programming/FPS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jamie/Programming/FPS

# Include any dependencies generated for this target.
include CMakeFiles/FPS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FPS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FPS.dir/flags.make

CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o: src/GJKAlgorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o -c /home/jamie/Programming/FPS/src/GJKAlgorithm.cpp

CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/GJKAlgorithm.cpp > CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.i

CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/GJKAlgorithm.cpp -o CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.s

CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.requires

CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.provides: CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.provides

CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.provides.build: CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o


CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o: src/GraphicsManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o -c /home/jamie/Programming/FPS/src/GraphicsManager.cpp

CMakeFiles/FPS.dir/src/GraphicsManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/GraphicsManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/GraphicsManager.cpp > CMakeFiles/FPS.dir/src/GraphicsManager.cpp.i

CMakeFiles/FPS.dir/src/GraphicsManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/GraphicsManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/GraphicsManager.cpp -o CMakeFiles/FPS.dir/src/GraphicsManager.cpp.s

CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.requires

CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.provides: CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.provides

CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.provides.build: CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o


CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o: src/GraphicsManagerFileLoaders.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o -c /home/jamie/Programming/FPS/src/GraphicsManagerFileLoaders.cpp

CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/GraphicsManagerFileLoaders.cpp > CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.i

CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/GraphicsManagerFileLoaders.cpp -o CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.s

CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.requires

CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.provides: CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.provides

CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.provides.build: CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o


CMakeFiles/FPS.dir/src/InputManager.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/InputManager.cpp.o: src/InputManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/FPS.dir/src/InputManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/InputManager.cpp.o -c /home/jamie/Programming/FPS/src/InputManager.cpp

CMakeFiles/FPS.dir/src/InputManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/InputManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/InputManager.cpp > CMakeFiles/FPS.dir/src/InputManager.cpp.i

CMakeFiles/FPS.dir/src/InputManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/InputManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/InputManager.cpp -o CMakeFiles/FPS.dir/src/InputManager.cpp.s

CMakeFiles/FPS.dir/src/InputManager.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/InputManager.cpp.o.requires

CMakeFiles/FPS.dir/src/InputManager.cpp.o.provides: CMakeFiles/FPS.dir/src/InputManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/InputManager.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/InputManager.cpp.o.provides

CMakeFiles/FPS.dir/src/InputManager.cpp.o.provides.build: CMakeFiles/FPS.dir/src/InputManager.cpp.o


CMakeFiles/FPS.dir/src/Math3d.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/Math3d.cpp.o: src/Math3d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/FPS.dir/src/Math3d.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/Math3d.cpp.o -c /home/jamie/Programming/FPS/src/Math3d.cpp

CMakeFiles/FPS.dir/src/Math3d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/Math3d.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/Math3d.cpp > CMakeFiles/FPS.dir/src/Math3d.cpp.i

CMakeFiles/FPS.dir/src/Math3d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/Math3d.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/Math3d.cpp -o CMakeFiles/FPS.dir/src/Math3d.cpp.s

CMakeFiles/FPS.dir/src/Math3d.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/Math3d.cpp.o.requires

CMakeFiles/FPS.dir/src/Math3d.cpp.o.provides: CMakeFiles/FPS.dir/src/Math3d.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/Math3d.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/Math3d.cpp.o.provides

CMakeFiles/FPS.dir/src/Math3d.cpp.o.provides.build: CMakeFiles/FPS.dir/src/Math3d.cpp.o


CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o: src/PhysicsEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o -c /home/jamie/Programming/FPS/src/PhysicsEngine.cpp

CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/PhysicsEngine.cpp > CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.i

CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/PhysicsEngine.cpp -o CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.s

CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.requires

CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.provides: CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.provides

CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.provides.build: CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o


CMakeFiles/FPS.dir/src/World.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/World.cpp.o: src/World.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/FPS.dir/src/World.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/World.cpp.o -c /home/jamie/Programming/FPS/src/World.cpp

CMakeFiles/FPS.dir/src/World.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/World.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/World.cpp > CMakeFiles/FPS.dir/src/World.cpp.i

CMakeFiles/FPS.dir/src/World.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/World.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/World.cpp -o CMakeFiles/FPS.dir/src/World.cpp.s

CMakeFiles/FPS.dir/src/World.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/World.cpp.o.requires

CMakeFiles/FPS.dir/src/World.cpp.o.provides: CMakeFiles/FPS.dir/src/World.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/World.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/World.cpp.o.provides

CMakeFiles/FPS.dir/src/World.cpp.o.provides.build: CMakeFiles/FPS.dir/src/World.cpp.o


CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o: src/component/renderable/Model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o -c /home/jamie/Programming/FPS/src/component/renderable/Model.cpp

CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/component/renderable/Model.cpp > CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.i

CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/component/renderable/Model.cpp -o CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.s

CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.requires

CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.provides: CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.provides

CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.provides.build: CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o


CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o: src/component/renderable/Renderable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o -c /home/jamie/Programming/FPS/src/component/renderable/Renderable.cpp

CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/component/renderable/Renderable.cpp > CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.i

CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/component/renderable/Renderable.cpp -o CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.s

CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.requires

CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.provides: CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.provides

CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.provides.build: CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o


CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o: src/component/renderable/WireframeBox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o -c /home/jamie/Programming/FPS/src/component/renderable/WireframeBox.cpp

CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/component/renderable/WireframeBox.cpp > CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.i

CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/component/renderable/WireframeBox.cpp -o CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.s

CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.requires

CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.provides: CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.provides

CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.provides.build: CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o


CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o: src/component/rigidbody/RigidBody.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o -c /home/jamie/Programming/FPS/src/component/rigidbody/RigidBody.cpp

CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/component/rigidbody/RigidBody.cpp > CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.i

CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/component/rigidbody/RigidBody.cpp -o CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.s

CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.requires

CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.provides: CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.provides

CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.provides.build: CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o


CMakeFiles/FPS.dir/src/entity/Box.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/entity/Box.cpp.o: src/entity/Box.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/FPS.dir/src/entity/Box.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/entity/Box.cpp.o -c /home/jamie/Programming/FPS/src/entity/Box.cpp

CMakeFiles/FPS.dir/src/entity/Box.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/entity/Box.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/entity/Box.cpp > CMakeFiles/FPS.dir/src/entity/Box.cpp.i

CMakeFiles/FPS.dir/src/entity/Box.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/entity/Box.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/entity/Box.cpp -o CMakeFiles/FPS.dir/src/entity/Box.cpp.s

CMakeFiles/FPS.dir/src/entity/Box.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/entity/Box.cpp.o.requires

CMakeFiles/FPS.dir/src/entity/Box.cpp.o.provides: CMakeFiles/FPS.dir/src/entity/Box.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/entity/Box.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/entity/Box.cpp.o.provides

CMakeFiles/FPS.dir/src/entity/Box.cpp.o.provides.build: CMakeFiles/FPS.dir/src/entity/Box.cpp.o


CMakeFiles/FPS.dir/src/entity/Entity.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/entity/Entity.cpp.o: src/entity/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/FPS.dir/src/entity/Entity.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/entity/Entity.cpp.o -c /home/jamie/Programming/FPS/src/entity/Entity.cpp

CMakeFiles/FPS.dir/src/entity/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/entity/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/entity/Entity.cpp > CMakeFiles/FPS.dir/src/entity/Entity.cpp.i

CMakeFiles/FPS.dir/src/entity/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/entity/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/entity/Entity.cpp -o CMakeFiles/FPS.dir/src/entity/Entity.cpp.s

CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.requires

CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.provides: CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.provides

CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.provides.build: CMakeFiles/FPS.dir/src/entity/Entity.cpp.o


CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o: src/entity/RotationObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o -c /home/jamie/Programming/FPS/src/entity/RotationObject.cpp

CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/entity/RotationObject.cpp > CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.i

CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/entity/RotationObject.cpp -o CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.s

CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.requires

CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.provides: CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.provides

CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.provides.build: CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o


CMakeFiles/FPS.dir/src/entity/Statue.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/entity/Statue.cpp.o: src/entity/Statue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/FPS.dir/src/entity/Statue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/entity/Statue.cpp.o -c /home/jamie/Programming/FPS/src/entity/Statue.cpp

CMakeFiles/FPS.dir/src/entity/Statue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/entity/Statue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/entity/Statue.cpp > CMakeFiles/FPS.dir/src/entity/Statue.cpp.i

CMakeFiles/FPS.dir/src/entity/Statue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/entity/Statue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/entity/Statue.cpp -o CMakeFiles/FPS.dir/src/entity/Statue.cpp.s

CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.requires

CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.provides: CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.provides

CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.provides.build: CMakeFiles/FPS.dir/src/entity/Statue.cpp.o


CMakeFiles/FPS.dir/src/main.cpp.o: CMakeFiles/FPS.dir/flags.make
CMakeFiles/FPS.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/FPS.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FPS.dir/src/main.cpp.o -c /home/jamie/Programming/FPS/src/main.cpp

CMakeFiles/FPS.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FPS.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jamie/Programming/FPS/src/main.cpp > CMakeFiles/FPS.dir/src/main.cpp.i

CMakeFiles/FPS.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FPS.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jamie/Programming/FPS/src/main.cpp -o CMakeFiles/FPS.dir/src/main.cpp.s

CMakeFiles/FPS.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/FPS.dir/src/main.cpp.o.requires

CMakeFiles/FPS.dir/src/main.cpp.o.provides: CMakeFiles/FPS.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/FPS.dir/build.make CMakeFiles/FPS.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/FPS.dir/src/main.cpp.o.provides

CMakeFiles/FPS.dir/src/main.cpp.o.provides.build: CMakeFiles/FPS.dir/src/main.cpp.o


# Object files for target FPS
FPS_OBJECTS = \
"CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o" \
"CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o" \
"CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o" \
"CMakeFiles/FPS.dir/src/InputManager.cpp.o" \
"CMakeFiles/FPS.dir/src/Math3d.cpp.o" \
"CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o" \
"CMakeFiles/FPS.dir/src/World.cpp.o" \
"CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o" \
"CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o" \
"CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o" \
"CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o" \
"CMakeFiles/FPS.dir/src/entity/Box.cpp.o" \
"CMakeFiles/FPS.dir/src/entity/Entity.cpp.o" \
"CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o" \
"CMakeFiles/FPS.dir/src/entity/Statue.cpp.o" \
"CMakeFiles/FPS.dir/src/main.cpp.o"

# External object files for target FPS
FPS_EXTERNAL_OBJECTS =

FPS: CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o
FPS: CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o
FPS: CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o
FPS: CMakeFiles/FPS.dir/src/InputManager.cpp.o
FPS: CMakeFiles/FPS.dir/src/Math3d.cpp.o
FPS: CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o
FPS: CMakeFiles/FPS.dir/src/World.cpp.o
FPS: CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o
FPS: CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o
FPS: CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o
FPS: CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o
FPS: CMakeFiles/FPS.dir/src/entity/Box.cpp.o
FPS: CMakeFiles/FPS.dir/src/entity/Entity.cpp.o
FPS: CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o
FPS: CMakeFiles/FPS.dir/src/entity/Statue.cpp.o
FPS: CMakeFiles/FPS.dir/src/main.cpp.o
FPS: CMakeFiles/FPS.dir/build.make
FPS: /usr/lib/libGL.so
FPS: /usr/lib/libGLU.so
FPS: /usr/lib/libglfw.so.3.2
FPS: CMakeFiles/FPS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jamie/Programming/FPS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking CXX executable FPS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FPS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FPS.dir/build: FPS

.PHONY : CMakeFiles/FPS.dir/build

CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/GJKAlgorithm.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/GraphicsManager.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/GraphicsManagerFileLoaders.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/InputManager.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/Math3d.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/PhysicsEngine.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/World.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/component/renderable/Model.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/component/renderable/Renderable.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/component/renderable/WireframeBox.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/component/rigidbody/RigidBody.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/entity/Box.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/entity/Entity.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/entity/RotationObject.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/entity/Statue.cpp.o.requires
CMakeFiles/FPS.dir/requires: CMakeFiles/FPS.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/FPS.dir/requires

CMakeFiles/FPS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FPS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FPS.dir/clean

CMakeFiles/FPS.dir/depend:
	cd /home/jamie/Programming/FPS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jamie/Programming/FPS /home/jamie/Programming/FPS /home/jamie/Programming/FPS /home/jamie/Programming/FPS /home/jamie/Programming/FPS/CMakeFiles/FPS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FPS.dir/depend

