cmake_minimum_required(VERSION 2.8)

project(ProjectEuler)
enable_testing()

if(MSVC)
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} /W4 /Od /ZI /EHsc "
        # The source code uses LL_FMT_STR wherever printf is passed a
        # long long value.  Unfortunately, microsoft requires the
        # format string to be %I64d instead of %lld.  Make it happen.
        "/DLL_FMT_STR=\\\"I64\\\"")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -O0 -g -std=c++11")
endif()

if(MINGW)
    # MinGW uses microsoft's back end, so the same reasoning applies.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLL_FMT_STR=\\\"I64\\\"")
endif()

message(${CMAKE_CXX_FLAGS})

set(INSTALL_ROOT ${CMAKE_SOURCE_DIR}/local)
set(INSTALL_LIB ${INSTALL_ROOT}/lib)
set(INSTALL_HDR ${INSTALL_ROOT}/include)
set(INSTALL_BIN ${INSTALL_ROOT}/bin)
set(INSTALL_EXTRA_FILES files)

set(COMMON_DIR Common)
include_directories(${COMMON_DIR})

add_subdirectory(1)
add_subdirectory(2)
add_subdirectory(3)
add_subdirectory(4)
add_subdirectory(5)
add_subdirectory(6)
add_subdirectory(7)
add_subdirectory(8)
add_subdirectory(9)
add_subdirectory(${COMMON_DIR})

add_subdirectory(MetaSandbox)
