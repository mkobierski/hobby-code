cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-Wall -g -O0")
include_directories("${CMAKE_SOURCE_DIR}/../Geometric")

project(Q42)
add_executable(Q42 main.cpp Q42.cpp)