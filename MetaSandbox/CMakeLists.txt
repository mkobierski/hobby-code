project(MetaSandbox)

set(SRC_COMMON
    main.cpp
    Conversion.hpp
    NullEmpty.hpp
    Select.hpp
    StaticAssert.hpp
    TypeList.hpp)
set(SRC_MAIN main.cpp)

add_executable(${PROJECT_NAME} ${SRC_MAIN} ${SRC_COMMON})

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${INSTALL_BIN})
