project(Common)

find_package(Boost 1.57.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions(-DHAVE_BOOST)
endif()

set(HDR_COMMON
               # BigNumber.hpp
               GlobalDefines.hpp
               CircularBuffer.hpp
               Common.hpp
               File.hpp
               LowestCommonMultiple.hpp
               Memory.hpp
               Palindrome.h
               Types.hpp
               Verify.hpp
               Prime/PrimeSeive.hpp
               Prime/PrimeSeive.hxx)

set(SRC_COMMON
               # BigNumber.cpp
               File.cpp
               LowestCommonMultiple.cpp
               Memory.cpp
               Palindrome.c)

add_library(Common ${SRC_COMMON} ${HDR_COMMON})

add_executable(Prime-test Prime-test.cpp
                          Prime/PrimeSeive.hpp
                          Prime/PrimeSeive.hxx)

add_test(NAME PrimeTestOK
         COMMAND Prime-test)

install(TARGETS Common
        DESTINATION ${INSTALL_LIB})

install(FILES ${HDR_COMMON}
        DESTINATION ${INSTALL_HDR})

install(DIRECTORY Prime
        DESTINATION ${INSTALL_HDR}
        FILES_MATCHING REGEX ".*\\.(h|hpp|hxx)$")