cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(Logger CXX)

option(ENABLE_CXX11 "Enables C++11 support" OFF)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/cmake)

find_package(Eigen3 3.0.0 REQUIRED)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})

if(ENABLE_CXX11)
   add_definitions(-DHAS_CXX11_SUPPORT)
   message(STATUS "C++11 support enabled")
   set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++0x")
else(ENABLE_CXX11)
   message(STATUS "C++11 support disabled")
   message(STATUS "  No logging functionality!")
   set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=gnu++98")
endif(ENABLE_CXX11)	

include_directories(src)

add_subdirectory(src)

add_subdirectory(tests)
