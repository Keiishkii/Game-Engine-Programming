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
		void Material::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			std::cout << subPath << std::endl;
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

			Document document;
			document.Parse(fileContent.c_str());

			GLuint shaderProgramID = 0;
			AssignShader(document);
			glUseProgram(shaderProgramID);

			AssignColour(document);
			AssignRoughness(document);
			AssignMetallic(document);

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
		}

		void Material::AssignRoughness(const Document& document)
		{
			if (document.HasMember("roughness") && (document["roughness"].IsFloat() || document["roughness"].IsInt()))
			{
				_roughness = document["roughness"].GetFloat();
			}
		}

		void Material::AssignMetallic(const Document& document)
		{
			if (document.HasMember("metallic") && (document["metallic"].IsFloat() || document["metallic"].IsInt()))
			{
				_metallic = document["metallic"].GetFloat();
			}
		}

		void Material::AssignAlbedoTexture(const Document& document)
		{
			if (document.HasMember("albedo_texture_map") && document["albedo_texture_map"].IsString())
			{
				_albedoTexture = _resourceManager.lock()->FindAsset<Texture>(document["albedo_texture_map"].GetString());
			}
		}

		void Material::AssignNormalTexture(const Document& document)
		{
			if (document.HasMember("normal_texture_map") && document["normal_texture_map"].IsString())
			{
				_normalTexture = _resourceManager.lock()->FindAsset<Texture>(document["normal_texture_map"].GetString());
			}
		}

		glm::vec4& Material::Colour() { return _colour; }
		float& Material::Roughness() { return _roughness; }
		float& Material::Metallic() { return _metallic; }
		std::shared_ptr<ShaderProgram>& Material::GetShaderProgram() { return _shaderProgram; }
		std::shared_ptr<Texture>& Material::GetAlbedoTexture() { return _albedoTexture; }
		std::shared_ptr<Texture>& Material::GetNormalTexture() { return _normalTexture; }
	}
}