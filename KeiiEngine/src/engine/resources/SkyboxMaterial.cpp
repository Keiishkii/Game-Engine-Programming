#include <fstream>
#include <iostream>

#include "SkyboxMaterial.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"
#include "engine/error-handling/Exception.h"
#include "ResourceManager.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void SkyboxMaterial::Load(const std::string& path)
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
			AssignAlbedoTextureCubeMap(document);

			glUseProgram(0);
		}

		void SkyboxMaterial::AssignShader(const Document& document)
		{
			if (document.HasMember("shader_program") && document["shader_program"].IsString())
			{
				std::shared_ptr<ShaderProgram> shaderProgram = _resourceManager.lock()->FindAsset<ShaderProgram>(document["shader_program"].GetString());
				_shaderProgram = shaderProgram;
			}
		}

		void SkyboxMaterial::AssignColour(const Document& document)
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

		void SkyboxMaterial::AssignAlbedoTextureCubeMap(const Document& document)
		{
			if (document.HasMember("albedo_texture_cube_map") && document["albedo_texture_cube_map"].IsString())
			{
				_albedoTextureCubeMap = _resourceManager.lock()->FindAsset<TextureCubeMap>(document["albedo_texture_cube_map"].GetString());
			}
		}

		glm::vec4& SkyboxMaterial::Colour() { return _colour; }
		std::shared_ptr<ShaderProgram>& SkyboxMaterial::GetShaderProgram() { return _shaderProgram; }
		std::shared_ptr<TextureCubeMap>& SkyboxMaterial::GetAlbedoTextureCubeMap() { return _albedoTextureCubeMap; }
	}
}