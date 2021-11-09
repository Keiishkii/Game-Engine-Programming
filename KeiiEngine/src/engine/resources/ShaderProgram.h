#pragma once
#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM
	#include <string>
	#include <memory>
	#include <glew.h>

	#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct ShaderProgram : Resource
		{
		private:
			GLuint _shaderProgramID;

		private:
			void GenerateVertexShader(std::string shader, GLuint& shaderID);
			void GenerateFragmentShader(std::string shader, GLuint& shaderID);
			void GenerateShaderAttributes(GLuint programID, std::string path);

		public:
			virtual void Load(std::string path) override;
			GLuint& GetShaderID();
		};
	}
}

#endif