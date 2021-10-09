cmake_minimum_required(VERSION 3.0)
project(KEIIENGINE)
add_executable(KeiiEngine
	src/engine/Main.cpp

	src/engine/KeiiEngine.h

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
