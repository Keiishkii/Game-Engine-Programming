cmake_minimum_required(VERSION 3.6)
project(KEIIENGINE)

set(CMAKE_CXX_STANDARD 20)


include_directories(
	src 					#For myengine.h
	contrib 				#For glm.hpp
)

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MT")

 	include_directories(
 		contrib/SDL2/include/SDL2 		#For SDL.h
 		contrib/glew/include/GL 		#For glew.h
		contrib/FBXSDK/include 			#For fbxsdk.h
		contrib/OpenAL/include 			#For OpenAL.h
		contrib/PhysX-4.1/include 		#For PhysX-4.1.h
	)
	link_directories(
 		${CMAKE_SOURCE_DIR}/contrib/SDL2/lib/x64
 		${CMAKE_SOURCE_DIR}/contrib/glew/lib/Release/x64
 		${CMAKE_SOURCE_DIR}/contrib/FBXSDK/lib/vs2017/x64/release
 		${CMAKE_SOURCE_DIR}/contrib/OpenAL/libs/Win64
 		${CMAKE_SOURCE_DIR}/contrib/PhysX-4.1/lib
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
	src/engine/SystemIndexer.cpp
	src/engine/SystemIndexer.h
	
	src/engine/Core.cpp
	src/engine/Core.h
	
	
		#Physics
	src/engine/physics/PhysicsManager.cpp
	src/engine/physics/PhysicsManager.h
	
	
		#Time
	src/engine/time/TimeManager.cpp
	src/engine/time/TimeManager.h


		#Inputs
	src/engine/input/InputManager.cpp
	src/engine/input/InputManager.h
	
	src/engine/input/Inputs.cpp
	src/engine/input/Inputs.h


		#Audio
	src/engine/audio/AudioManager.cpp
	src/engine/audio/AudioManager.h
	
	src/engine/audio/AudioBuffer.cpp
	src/engine/audio/AudioBuffer.h
	
	
		#Graphics
	src/engine/graphics/GraphicsManager.cpp
	src/engine/graphics/GraphicsManager.h
			
	src/engine/graphics/VertexBuffer.cpp
	src/engine/graphics/VertexBuffer.h
	
	src/engine/graphics/VertexArray.cpp
	src/engine/graphics/VertexArray.h
	
	src/engine/graphics/PolygonMaterialGroup.cpp
	src/engine/graphics/PolygonMaterialGroup.h
		
		
		#Entitys
	src/engine/Entity.cpp
	src/engine/Entity.h
		
		
		#Scenes
	src/engine/Scene.cpp
	src/engine/Scene.h
		
		
		#Components
	src/engine/components/Component.cpp
	src/engine/components/Component.h
	
	src/engine/components/AudioSource.cpp
	src/engine/components/AudioSource.h
	
	src/engine/components/AudioListener.cpp
	src/engine/components/AudioListener.h

	src/engine/components/Transform.cpp
	src/engine/components/Transform.h

	src/engine/components/ReflectionProbe.cpp
	src/engine/components/ReflectionProbe.h
	
	src/engine/components/Camera.cpp
	src/engine/components/Camera.h

	src/engine/components/Light.cpp
	src/engine/components/Light.h

	src/engine/components/Gizmo.cpp
	src/engine/components/Gizmo.h
	
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

	src/engine/resources/TextureCubeMap.cpp
	src/engine/resources/TextureCubeMap.h

	src/engine/resources/Material.cpp
	src/engine/resources/Material.h

	src/engine/resources/SkyboxMaterial.cpp
	src/engine/resources/SkyboxMaterial.h

	src/engine/resources/AudioClip.cpp
	src/engine/resources/AudioClip.h
)


target_link_libraries(keiiengine
	SDL2
	glew32
	openGL32
	libfbxsdk
	OpenAL32
	
	LowLevel_static_64
	LowLevelAABB_static_64
	LowLevelDynamics_static_64
	PhysX_64
	PhysXCharacterKinematic_static_64
	PhysXCommon_64
	PhysXCooking_64
	PhysXExtensions_static_64
	PhysXFoundation_64
	PhysXPvdSDK_static_64
	PhysXTask_static_64
	PhysXVehicle_static_64
	SceneQuery_static_64
	SimulationController_static_64
	SnippetRender_static_64
	SnippetUtils_static_64
)

add_executable(game
	src/game/Main.cpp

		#Custom Scenes
	src/game/CustomScene.cpp
	src/game/CustomScene.h

		#Components
	src/game/components/PlayerController.cpp
	src/game/components/PlayerController.h
	
	src/game/components/Rotator.cpp
	src/game/components/Rotator.h

	src/game/components/CameraController.cpp
	src/game/components/CameraController.h

	src/game/components/ShaderTextureSampler.cpp
	src/game/components/ShaderTextureSampler.h
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
	configure_file(contrib/OpenAL/OpenAL32.dll OpenAL32.dll COPYONLY)
	
		#PhysX
	configure_file(contrib/PhysX-4.1/dlls/glut32.dll glut32.dll COPYONLY)
	configure_file(contrib/PhysX-4.1/dlls/PhysX_64.dll PhysX_64.dll COPYONLY)
	configure_file(contrib/PhysX-4.1/dlls/PhysXCommon_64.dll PhysXCommon_64.dll COPYONLY)
	configure_file(contrib/PhysX-4.1/dlls/PhysXCooking_64.dll PhysXCooking_64.dll COPYONLY)
	configure_file(contrib/PhysX-4.1/dlls/PhysXDevice64.dll PhysXDevice64.dll COPYONLY)
	configure_file(contrib/PhysX-4.1/dlls/PhysXFoundation_64.dll PhysXFoundation_64.dll COPYONLY)
	configure_file(contrib/PhysX-4.1/dlls/PhysXGpu_64.dll PhysXGpu_64.dll COPYONLY)
endif()

Message (\n Build  Succesful \n)