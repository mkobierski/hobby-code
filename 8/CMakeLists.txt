project(Q8)

set(SRC_COMMON Q8.cpp Q8.hpp Q8.hxx)
set(SRC_MAIN main.cpp)
set(SRC_TEST Q8-test.cpp)
set(EXTRA_FILES seq.txt)

add_executable(${PROJECT_NAME} ${SRC_MAIN} ${SRC_COMMON})
target_link_libraries (${PROJECT_NAME} Common)

add_executable(${PROJECT_NAME}-test ${SRC_TEST} ${SRC_COMMON})
target_link_libraries (${PROJECT_NAME}-test Common)

file(COPY ${EXTRA_FILES}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${INSTALL_EXTRA_FILES})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-test
        DESTINATION ${INSTALL_BIN})
install(FILES ${EXTRA_FILES}
        DESTINATION ${INSTALL_BIN}/${INSTALL_EXTRA_FILES})

add_test(NAME ${PROJECT_NAME}TestOK
         COMMAND ${PROJECT_NAME}-test)