#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "ShaderProgram.h"
#include "Texture.h"
#include "TextureCubeMap.h"
#include "engine/graphics/PolygonMaterialGroup.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void ShaderProgram::UseShader()
		{
			glUseProgram(_shaderProgramID);
		}

		void ShaderProgram::StopUsingShader()
		{
			glUseProgram(0);
		}



		#pragma region Set Uniforms

		void ShaderProgram::SetUniform(std::string unifromLocation, float data)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform1fv(uniformID, 1, &data);
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::vec2 data)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform2fv(uniformID, 1, glm::value_ptr(data));
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::vec3 data)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform3fv(uniformID, 1, glm::value_ptr(data));
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::vec4 data)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform4fv(uniformID, 1, glm::value_ptr(data));
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::mat4x4 data)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(data));
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, std::shared_ptr<Texture> data)
		{
			GLint uniformID = GetUniformID(unifromLocation);

			glUniform1i(uniformID, 0);
			glActiveTexture(GL_TEXTURE0);

			glBindTexture(GL_TEXTURE_2D, data->GetTextureID());
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, std::shared_ptr<TextureCubeMap> data)
		{
			GLint uniformID = GetUniformID(unifromLocation);

			glUniform1i(uniformID, 0);
			glActiveTexture(GL_TEXTURE0);

			glBindTexture(GL_TEXTURE_CUBE_MAP, data->GetCubeMapTextureID());
		}


		void ShaderProgram::SetUniform(std::string unifromLocation, float data[], int count)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform1fv(uniformID, count, &data[0]);
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::vec2 data[], int count)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform2fv(uniformID, count, glm::value_ptr(data[0]));
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::vec3 data[], int count)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform3fv(uniformID, count, glm::value_ptr(data[0]));
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::vec4 data[], int count)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniform4fv(uniformID, count, glm::value_ptr(data[0]));
		}

		void ShaderProgram::SetUniform(std::string unifromLocation, glm::mat4x4 data[], int count)
		{
			GLint uniformID = GetUniformID(unifromLocation);
			glUniformMatrix4fv(uniformID, count, GL_FALSE, glm::value_ptr(data[0]));
		}

		#pragma endregion



		#pragma region Draw Triangles

		void ShaderProgram::DrawTriangles(std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup,	std::shared_ptr<ShaderProgram> shaderProgram)
		{
			glBindVertexArray(polygonMaterialGroup->VertexArrayID(shaderProgram));
			glDrawArrays(GL_TRIANGLES, 0, polygonMaterialGroup->VertexCount());
		}

		void ShaderProgram::DrawTriangles(GLuint meshID, int vertexCount)
		{
			glBindVertexArray(meshID);
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		}

		#pragma endregion



		GLuint ShaderProgram::GetShaderID()
		{
			return _shaderProgramID;
		}

		GLint ShaderProgram::GetAttributeID(const std::string& attributeLocation)
		{
			GLint attributeID = 0;
			if (!_attributeIDMap.count(attributeLocation)) [[unlikely]]
			{
				attributeID = glGetAttribLocation(_shaderProgramID, attributeLocation.c_str());
				_attributeIDMap.insert(std::pair<std::string, GLint>(attributeLocation, attributeID));
			}
			else
			{
				attributeID = _attributeIDMap[attributeLocation];
			}

			return attributeID;
		}

		GLint ShaderProgram::GetUniformID(const std::string& unifromLocation)
		{
			GLint uniformID = 0;
			if (!_uniformIDMap.count(unifromLocation)) [[unlikely]]
			{
				uniformID = glGetUniformLocation(_shaderProgramID, unifromLocation.c_str());
				_uniformIDMap.insert(std::pair<std::string, GLint>(unifromLocation, uniformID));
			}
			else
			{
				uniformID = _uniformIDMap[unifromLocation];
			}

			return uniformID;
		}



		void ShaderProgram::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			_name = subPath;

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
	}
}