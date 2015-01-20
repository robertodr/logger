cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(Logger CXX)

option(ENABLE_CXX11 "Enables C++11 support" OFF)

if(ENABLE_CXX11)
   add_definitions(-DHAS_CXX11_SUPPORT)
endif()	

message(STATUS "C++11 support enabled")
set(CMAKE_CXX_FLAGS "-fPIC -std=c++0x")
include_directories(src/c++0x_logger)

add_subdirectory(src)

add_subdirectory(tests)
