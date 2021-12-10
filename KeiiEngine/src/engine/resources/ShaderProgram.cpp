#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "ShaderProgram.h"
#include "Texture.h"
#include "TextureCubeMap.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void ShaderProgram::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			std::string path = resourcesDirectory + subPath;
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

		void ShaderProgram::GenerateShaderAttributes(GLuint programID, const std::string& fileContent)
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

				glBindAttribLocation(programID, i, attributeName.c_str());
			}
		}

		void ShaderProgram::UploadTextureMapToShader(const std::shared_ptr<Texture>& textureMap, const std::string& sample)
		{
			glUniform1i(GetTextureSampleID(sample), 0);

			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_2D, textureMap->GetTextureID());
		}

		void ShaderProgram::UploadTextureMapToShader(const std::shared_ptr<TextureCubeMap>& textureMap, const std::string& sample)
		{
			glUniform1i(GetTextureSampleID(sample), 0);

			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureMap->GetCubeMapTextureID());
		}

		GLuint& ShaderProgram::GetShaderID()
		{
			return _shaderProgramID;
		}

		GLuint ShaderProgram::GetTextureSampleID(const std::string& sample)
		{
			GLuint sampleID = 0;
			if (_textureMapSampleIDs.count(sample))
			{
				sampleID = _textureMapSampleIDs[sample];
			}
			else
			{
				sampleID = glGetUniformLocation(_shaderProgramID, sample.c_str());
			}

			return sampleID;
		}
	}
}