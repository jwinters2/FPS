cmake_minimum_required (VERSION 2.6)
project (FPS)

#version number
set(FPS_VERSION_MAJOR 0)
set(FPS.VERSION_MINOR 1)

#C++ standard (equivalent to --std=c++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

include_directories(${FPS_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(FPS ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

target_link_libraries(FPS ${OPENGL_LIBRARIES} GLEW glfw glm)
