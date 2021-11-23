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
		void Material::Load(const std::string& path)
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
			AssignShader(document);
			glUseProgram(shaderProgramID);

			AssignColour(document);
			AssignAlbedoTexture(document);
			AssignNormalTexture(document);

			glUseProgram(0);
		}

		void Material::AssignShader(const Document& document)
		{
			if (document.HasMember("shader_program") && document["shader_program"].IsString())
			{
				std::shared_ptr<ShaderProgram> shaderProgram = _resourceManager.lock()->FindAsset<ShaderProgram>(document["shader_program"].GetString());
				_shaderProgram = shaderProgram;
			}
			else
			{
				//std::cout << " - - Material had no shader attached" << std::endl;
			}
		}

		void Material::AssignColour(const Document& document)
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
			}
			else
			{
				//std::cout << " - - Material had no shader colour" << std::endl;
			}
		}

		void Material::AssignAlbedoTexture(const Document& document)
		{
			if (document.HasMember("albedo_texture_map") && document["albedo_texture_map"].IsString())
			{
				_albedoTexture = _resourceManager.lock()->FindAsset<Texture>(document["albedo_texture_map"].GetString());
			}
			else
			{
				//std::cout << " - - Material had no albedo map attached" << std::endl;
			}
		}

		void Material::AssignNormalTexture(const Document& document)
		{
			if (document.HasMember("normal_texture_map") && document["normal_texture_map"].IsString())
			{
				_normalTexture = _resourceManager.lock()->FindAsset<Texture>(document["normal_texture_map"].GetString());
			}
			else
			{
				//std::cout << " - - Material had no normal map attached" << std::endl;
			}
		}

		glm::vec4& Material::Colour() { return _colour; }
		std::shared_ptr<ShaderProgram>& Material::GetShaderProgram() { return _shaderProgram; }
		std::shared_ptr<Texture>& Material::GetAlbedoTexture() { return _albedoTexture; }
		std::shared_ptr<Texture>& Material::GetNormalTexture() { return _normalTexture; }
	}
}