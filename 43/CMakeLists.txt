cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_library(43 43.cpp)
add_executable(test_43 main.cpp)
target_link_libraries(test_43 43)
