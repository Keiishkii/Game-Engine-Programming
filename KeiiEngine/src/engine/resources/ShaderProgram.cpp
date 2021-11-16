#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "ShaderProgram.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void ShaderProgram::Load(std::string path)
		{
			std::string fileContent = "";

			std::fstream fileStream;
			fileStream.open(path);

			if (fileStream.is_open())
			{
				std::string fileLine = "";
				while (std::getline(fileStream, fileLine))
				{
					fileContent += fileLine + "\n";
				}
			}

			GLuint vertexShaderID = 0;
			GenerateVertexShader(fileContent, vertexShaderID);

			GLuint fragmentShaderID = 0;
			GenerateFragmentShader(fileContent, fragmentShaderID);

			GLuint programId = glCreateProgram();

			glAttachShader(programId, vertexShaderID);
			glAttachShader(programId, fragmentShaderID);

			GenerateShaderAttributes(programId, fileContent);

			GLint success = 0;
			glLinkProgram(programId);
			glGetProgramiv(programId, GL_LINK_STATUS, &success);

			if (success)
			{
				_shaderProgramID = programId;
			}
			else
			{
				throw ErrorHandling::Exception("Failed to create the shader program.");
			}

			glDetachShader(programId, vertexShaderID);
			glDeleteShader(vertexShaderID);
			glDetachShader(programId, fragmentShaderID);
			glDeleteShader(fragmentShaderID);
		}

		void ShaderProgram::GenerateVertexShader(std::string shader, GLuint& shaderID)
		{
			std::string vertexShader = "#define VERTEX_SHADER\n" + shader;
			const char* vertexShader_cStr = vertexShader.c_str();

			shaderID = glCreateShader(GL_VERTEX_SHADER);

			glShaderSource(shaderID, 1, &vertexShader_cStr, NULL);
			glCompileShader(shaderID);

			GLint success = 0;

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				throw ErrorHandling::Exception("Failed to compile vertex shader.");
			}
		}

		void ShaderProgram::GenerateFragmentShader(std::string shader, GLuint& shaderID)
		{
			std::string fragmentShader = "#define FRAGMENT_SHADER\n" + shader;
			const char* fragmentShader_cStr = fragmentShader.c_str();

			shaderID = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(shaderID, 1, &fragmentShader_cStr, NULL);
			glCompileShader(shaderID);

			GLint success = 0;

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				throw ErrorHandling::Exception("Failed to compile fragment shader.");
			}
		}

		void ShaderProgram::GenerateShaderAttributes(GLuint programID, std::string fileContent)
		{
			std::string line;
			std::vector<std::string> lines;
			std::stringstream lineStream(fileContent);

			while (std::getline(lineStream, line, '\n'))
			{
				if (line.find("attribute") != std::string::npos)
				{
					lines.push_back(line);
				}
			}

			for (int i = 0; i < lines.size(); i++)
			{
				std::string word;
				std::vector<std::string> words;
				std::stringstream wordStream(lines[i]);

				while (std::getline(wordStream, word, ' '))
				{
					words.push_back(word);
				}
				
				std::string attribute = words[words.size() - 1];

				std::string attributeName = attribute.substr(0, attribute.size() - 1);
				std::cout << "SHADER ATTRIBUTE: " << attributeName << std::endl;

				glBindAttribLocation(programID, i, attributeName.c_str());
				//glBindAttribLocation(programID, 1, attribute.substr(0, attribute.size() - 1).c_str());
			}
		}

		GLuint& ShaderProgram::GetShaderID()
		{
			return _shaderProgramID;
		}
	}
}