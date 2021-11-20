#include <fstream>
#include <iostream>

#include "Material.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "engine/error-handling/Exception.h"
#include "ResourceManager.h"

namespace Engine
{
	namespace ResourceManagement
	{
		std::shared_ptr<ShaderProgram> Material::GetShaderProgram() { return _shaderProgram.lock(); }
		
		glm::vec4 Material::GetColour() { return _colour; }

		std::shared_ptr<Texture> Material::GetAlbedoTexture() { return _albedoTexture.lock(); }

		std::shared_ptr<Texture> Material::GetNormalTexture() { return _normalTexture.lock(); }

		void Material::Load(std::string path)
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

			Document document;
			document.Parse(fileContent.c_str());

			GLuint shaderProgramID = 0;
			AssignShader(document, shaderProgramID);
			glUseProgram(shaderProgramID);

			AssignColour(document);
			AssignAlbedoTexture(document, shaderProgramID);
			AssignNormalTexture(document, shaderProgramID);

			glUseProgram(0);
		}

		void Material::AssignShader(Document& document, GLuint& shaderProgramID)
		{
			if (document.HasMember("shader_program") && document["shader_program"].IsString())
			{
				std::shared_ptr<ShaderProgram> shaderProgram = _resourceManager.lock()->FindAsset<ShaderProgram>(document["shader_program"].GetString());
				_shaderProgram = shaderProgram;
				
				shaderProgramID = shaderProgram->GetShaderID();
			}
			else
			{
				std::cout << " - - Material had no shader attached" << std::endl;
			}
		}

		void Material::AssignColour(Document& document)
		{
			if (document.HasMember("colour") && document["colour"].IsArray())
			{
				const Value& colour = document["colour"];
				if (colour.Size() == 3)
				{
					_colour = glm::vec4(colour[0].GetFloat(), colour[1].GetFloat(), colour[2].GetFloat(), 1);
				}
				else if (colour.Size() == 4)
				{
					_colour = glm::vec4(colour[0].GetFloat(), colour[1].GetFloat(), colour[2].GetFloat(), colour[3].GetFloat());
				}

				std::cout << "Colour: [" << _colour.x << ", " << _colour.y << ", " << _colour.z << ", " << _colour.w << "]" << std::endl;
			}
			else
			{
				std::cout << " - - Material had no shader colour" << std::endl;
			}
		}

		void Material::AssignAlbedoTexture(Document& document, GLuint& shaderProgramID)
		{
			if (document.HasMember("albedo_texture_map") && document["albedo_texture_map"].IsString())
			{
				std::shared_ptr<Texture> albedoTexture = _resourceManager.lock()->FindAsset<Texture>(document["albedo_texture_map"].GetString());
				_albedoTexture = albedoTexture;

				GLint textureLoc = glGetUniformLocation(shaderProgramID, "in_Texture");

				GLuint textureId = 0;
				glGenTextures(1, &textureId);

				if (!textureId)
				{
					throw ErrorHandling::Exception("Failed to create a texture ID for the albedo texture.");
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, textureId);

					// Upload the image data to the bound texture unit in the GPU
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, albedoTexture->GetWidth(), albedoTexture->GetHeight(), 0, GL_RGBA,
						GL_UNSIGNED_BYTE, albedoTexture->GetTexture());

					// Free the loaded data because we now have a copy on the GPU
					free(albedoTexture->GetTexture());
					glGenerateMipmap(GL_TEXTURE_2D);
					/////////////////////

					glUniform1i(textureLoc, 0);

					glActiveTexture(GL_TEXTURE0 + 0);
					glBindTexture(GL_TEXTURE_2D, textureId);
				}
			}
			else
			{
				std::cout << " - - Material had no albedo map attached" << std::endl;
			}
		}

		void Material::AssignNormalTexture(Document& document, GLuint& shaderProgramID)
		{
			if (document.HasMember("normal_texture_map") && document["normal_texture_map"].IsString())
			{
				_normalTexture = _resourceManager.lock()->FindAsset<Texture>(document["normal_texture_map"].GetString());
			}
			else
			{
				std::cout << " - - Material had no normal map attached" << std::endl;
			}
		}
	}
}