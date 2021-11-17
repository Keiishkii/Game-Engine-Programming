cmake_minimum_required(VERSION 3.6)
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
 		${CMAKE_SOURCE_DIR}/contrib/FBXSDK/lib/vs2017/x64/release
	)
else()
 	#Linux, Emscripten, macOS equivalents
endif()



if(MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(keiiengine
	src/engine/KeiiEngine.h

		#Error Handling
	src/engine/error-handling/Exception.cpp
	src/engine/error-handling/Exception.h
	
	src/engine/error-handling/Debugger.cpp
	src/engine/error-handling/Debugger.h


		#Core
	src/engine/Core.cpp
	src/engine/Core.h

	src/engine/Enviroment.cpp
	src/engine/Enviroment.h

	src/engine/TimeManager.cpp
	src/engine/TimeManager.h


		#Graphics
	src/engine/graphics/VertexBuffer.cpp
	src/engine/graphics/VertexBuffer.h
	
	src/engine/graphics/VertexArray.cpp
	src/engine/graphics/VertexArray.h
	
	src/engine/graphics/PolygonMaterialGroup.cpp
	src/engine/graphics/PolygonMaterialGroup.h
		
		
		#Entitys
	src/engine/Entity.cpp
	src/engine/Entity.h
		
		
		#Components
	src/engine/components/Component.cpp
	src/engine/components/Component.h

	src/engine/components/Transform.cpp
	src/engine/components/Transform.h

	src/engine/components/Camera.cpp
	src/engine/components/Camera.h
	
	src/engine/components/MeshRenderer.cpp
	src/engine/components/MeshRenderer.h
	
	
		#Resources
	src/engine/resources/ResourceManager.cpp
	src/engine/resources/ResourceManager.h

	src/engine/resources/Resource.cpp
	src/engine/resources/Resource.h

	src/engine/resources/ShaderProgram.cpp
	src/engine/resources/ShaderProgram.h

	src/engine/resources/Model.cpp
	src/engine/resources/Model.h

	src/engine/resources/Texture.cpp
	src/engine/resources/Texture.h

	src/engine/resources/Material.cpp
	src/engine/resources/Material.h

	src/engine/resources/Sound.cpp
	src/engine/resources/Sound.h
)


target_link_libraries(keiiengine
	SDL2
	glew32
	openGL32
	libfbxsdk
)

add_executable(game
	src/game/Main.cpp

	src/game/components/PlayerController.cpp
	src/game/components/PlayerController.h
)

target_link_libraries(game keiiengine)



# Tidy up project

if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
	
	# Macro to preserve source files hierarchy in the IDE
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

		foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
				GroupSources(${curdir}/${child})
			else()
				string(REPLACE "/" "\\" groupname ${curdir})
				string(REPLACE "src" "Sources" groupname ${groupname})
				source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			endif()
		endforeach()
	endmacro()

	# Run macro
	GroupSources(src)
endif()

if(WIN32)
	configure_file(contrib/SDL2/lib/x64/SDL2.dll SDL2.dll COPYONLY)
	configure_file(contrib/FBXSDK/lib/vs2017/x64/debug/libfbxsdk.dll libfbxsdk.dll COPYONLY)
	configure_file(contrib/glew/bin/Release/x64/glew32.dll glew32.dll COPYONLY)
endif()

Message (\n Build  Succesful \n)