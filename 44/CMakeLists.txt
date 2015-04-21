cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-Wall -g -O0")
include_directories("${CMAKE_SOURCE_DIR}/../Geometric")

project(Q44)
add_executable(Q44 main.cpp Q44.cpp)