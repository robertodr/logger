cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(Logger CXX)

set(CMAKE_CXX_FLAGS "-fPIC -std=c++11")

add_subdirectory(src)

include_directories(src/logger)
include_directories(src/c++0x_logger)

add_subdirectory(tests)
