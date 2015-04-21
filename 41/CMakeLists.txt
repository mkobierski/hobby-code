cmake_minimum_required(VERSION 2.6)

if (UNIX OR MINGW)
  message(status "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
endif()

project(Q41)
add_library(Q41 Q41.cpp)
add_executable(test_Q41 main.cpp)
target_link_libraries(test_Q41 Q41)
