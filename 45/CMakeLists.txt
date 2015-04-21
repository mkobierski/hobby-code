cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-Wall -g -O0")
include_directories("${CMAKE_SOURCE_DIR}/../Geometric")

project(Q45)
add_executable(Q45 main.cpp)