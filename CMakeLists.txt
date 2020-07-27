cmake_minimum_required (VERSION 2.8)
project (Roulette)

#version number of software
set (R_VERSION_MAJOR 1)
set (R_VERSION_MINOR 0)
set (R_VERSION_PATCH 0)

add_definitions(-D_CRT_SECURE_NO_WARNINGS) 
#add_definitions(-DDEV_LINUX)

set(BOOST_ROOT_DIR "$ENV{BOOST_ROOT_DIR}")
include_directories("${BOOST_ROOT_DIR}")
include_directories("include")

file (GLOB inc "*.h")
file(GLOB src "main.cpp")
file(GLOB TEST_SRC "test.cpp")

source_group("Header Files" FILES ${inc})
source_group("Source Files" FILES ${src})

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)    #Debug
endif()

add_executable (Roulette ${src} )
add_executable (TestRoulette ${TEST_SRC} )