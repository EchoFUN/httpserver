cmake_minimum_required(VERSION 3.5.2)
project(httpserver CXX)

set(CMAKE_CXX_STANDARD 14)


set(CC "g++")
set(SRCDIR "src")
set(BINDIR "bin")
set(BUILDDIR "build")
set(TARGET "httpserver")

# CMAKE_SYSTEM_NAME equals $(shell name)

# Debug Flags
set(DEBUGFLAGS "-g3 -O0 -Wall -fmudflap")

# Production Flags
set(PRODFLAGS "-Wall -O2 -fstack-check -fstack-protector-all")

set(CFLAGS "-std=c++14 -Iinclude/ ${PRODFLAGS}")
set(LINK ${PRODFLAGS})

include_directories(${SRCDIR})
set(SRCEXT "cpp")

file(GLOB SOURCES ${SRCDIR}/*.${SRCEXT})
file(MAKE_DIRECTORY ${BUILDDIR})




# set(OBJECTS "")


add_executable(httpserver ${SOURCES})