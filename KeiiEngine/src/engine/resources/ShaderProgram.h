#pragma once
#ifndef SHADER
#define SHADER
	#include <string>
	#include <glew.h>

	#include "Resource.h"

	namespace Engine
	{
		namespace ResourceManagement
		{
			struct ShaderProgram : Resource
			{
			private:
				GLuint _shaderID;
			
			public:
				virtual void Load(std::string path) override;
				GLuint GetShader();
			};
		}
	}
#endif