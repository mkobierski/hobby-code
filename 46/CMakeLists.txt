cmake_minimum_required(VERSION 3.1)

if (UNIX OR MINGW)
  message(status "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
endif()

include_directories("${CMAKE_SOURCE_DIR}/../")

project(Q46)
add_executable(Q46 main.cpp)