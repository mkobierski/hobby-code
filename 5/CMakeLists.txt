project(Q5)

set(SRC_COMMON Q5.cpp Q5.hpp)
set(SRC_MAIN main.cpp)
set(SRC_TEST Q5-test.cpp)

add_executable(${PROJECT_NAME} ${SRC_MAIN} ${SRC_COMMON})
target_link_libraries (${PROJECT_NAME} Common)

add_executable(${PROJECT_NAME}-test ${SRC_TEST} ${SRC_COMMON})
target_link_libraries (${PROJECT_NAME}-test Common)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-test
        DESTINATION ${INSTALL_BIN})

add_test(NAME ${PROJECT_NAME}TestOK
         COMMAND ${PROJECT_NAME}-test)