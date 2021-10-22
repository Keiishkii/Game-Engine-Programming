cmake_minimum_required(VERSION 3.0)
project(KEIIENGINE)


include_directories(
 src # For myengine.h
 contrib # For glm.hpp
)

if(MSVC)
 include_directories(
 contrib/SDL2/include # For SDL.h
 contrib/glew/include # For glew.h
 )
 link_directories(
 ${CMAKE_SOURCE_DIR}/contrib/SDL2/lib/x86
 )
else()
 # Linux, Emscripten, macOS equivalents
endif()

if(MSVC)
 add_definitions(-DSDL_MAIN_HANDLED)
endif()


add_executable(KeiiEngine
	src/engine/Main.cpp

	src/engine/KeiiEngine.h
	
	src/engine/Debugger.cpp
	src/engine/Debugger.h

	src/engine/Core.cpp
	src/engine/Core.h

	src/engine/Entity.cpp
	src/engine/Entity.h

	src/engine/Component.cpp
	src/engine/Component.h

	src/engine/Enviroment.cpp
	src/engine/Enviroment.h

	src/engine/Time.cpp
	src/engine/Time.h
)