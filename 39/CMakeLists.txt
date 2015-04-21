project(q39)

if(MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
endif(MINGW)


add_executable(Q39 q39.cpp)