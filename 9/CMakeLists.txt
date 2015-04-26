project(Q9)

set(SRC_COMMON Q9.cpp Q9.hpp)
set(SRC_MAIN main.cpp)
set(SRC_TEST Q9-test.cpp)

add_executable(${PROJECT_NAME} ${SRC_MAIN} ${SRC_COMMON})
add_executable(${PROJECT_NAME}-test ${SRC_TEST} ${SRC_COMMON})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-test
        DESTINATION ${INSTALL_BIN})

add_test(NAME ${PROJECT_NAME}TestOK
            COMMAND ${PROJECT_NAME}-test)
