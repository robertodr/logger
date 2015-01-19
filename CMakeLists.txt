cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(Logger CXX)

option(ENABLE_CXX11 "Enables C++11 support" OFF)

find_package(Boost 1.54 COMPONENTS thread REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_subdirectory(src)

if(ENABLE_CXX11)
   set(CMAKE_CXX_FLAGS "-fPIC -std=c++11")
   include_directories(src/c++0x_logger)
else(ENABLE_CXX11)
   set(CMAKE_CXX_FLAGS "-fPIC -std=gnu++98")
   include_directories(src/boost_logger)
endif(ENABLE_CXX11)

add_subdirectory(tests)
