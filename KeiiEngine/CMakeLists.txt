cmake_minimum_required(VERSION 3.0)
project(KEIIENGINE)



include_directories(
	src 					#For myengine.h
	contrib 				#For glm.hpp
)

if(MSVC)
 	include_directories(
 		contrib/SDL2/include/SDL2 	#For SDL.h
 		contrib/glew/include/GL 	#For glew.h
		contrib/FBXSDK/include 		#For fbxsdk.h
	)
	link_directories(
 		${CMAKE_SOURCE_DIR}/contrib/SDL2/lib/x64
 		${CMAKE_SOURCE_DIR}/contrib/glew/lib/Release/x64
 		${CMAKE_SOURCE_DIR}/contrib/FBXSDK/lib/vs2017/x64/debug
	)
else()
 	#Linux, Emscripten, macOS equivalents
endif()



if(MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()


add_library(glm "contrib/glm/glm.hpp")
add_library(keiiengine
	src/engine/Main.cpp

	src/engine/KeiiEngine.h
	
	src/engine/Debugger.cpp
	src/engine/Debugger.h

		#Core
	src/engine/Core.cpp
	src/engine/Core.h

	src/engine/Enviroment.cpp
	src/engine/Enviroment.h

	src/engine/Time.cpp
	src/engine/Time.h

		#Entitys
	src/engine/Entity.cpp
	src/engine/Entity.h
		
		#Components
	src/engine/components/Component.cpp
	src/engine/components/Component.h

	src/engine/components/Transform.cpp
	src/engine/components/Transform.h
)


target_link_libraries(keiiengine
	SDL2
	glew32
	openGL32
	libfbxsdk
)

add_executable(game
	src/engine/main.cpp
)

target_link_libraries(game keiiengine)