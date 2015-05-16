cmake_minimum_required(VERSION 3.0)
project(tree)
add_executable(prog main.cpp baum.cpp writer.cpp)

SET(GCC_COMPILE "-std=c++14 -Wall -pedantic")
SET(GCC_LINKER  "")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINKER}")

#ADD_CUSTOM_TARGET(cleanest COMMAND "rm -fr CMakeFiles cmake_install.cmake CMakeCache.txt Makefile")
