#include <iostream>

#include "SkyboxMaterial.h"
#include "ShaderProgram.h"
#include "TextureCubeMap.h"
#include "Texture.h"
#include "engine/error-handling/Exception.h"
#include "ResourceManager.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void SkyboxMaterial::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			std::string jsonString = ResourceManager::ReadText(resourcesDirectory + subPath);
			Document document = ResourceManager::ToJSON(jsonString);

			AssignShader(document);

			AssignColour(document);
			AssignAlbedoTextureCubeMap(document);
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
			_albedoTextureCubeMap = ResourceManager()->Create<ResourceManagement::TextureCubeMap>();

			if (document.HasMember("albedo_right") && document["albedo_right"].IsString())
			{
				std::string folderDirectory = document["albedo_right"].GetString();
				_albedoTextureCubeMap->RightTexture() = _resourceManager.lock()->FindAsset<Texture>(document["albedo_right"].GetString());
			}

			if (document.HasMember("albedo_left") && document["albedo_left"].IsString())
			{
				std::string folderDirectory = document["albedo_left"].GetString();
				_albedoTextureCubeMap->LeftTexture() = _resourceManager.lock()->FindAsset<Texture>(document["albedo_left"].GetString());
			}

			if (document.HasMember("albedo_top") && document["albedo_top"].IsString())
			{
				std::string folderDirectory = document["albedo_top"].GetString();
				_albedoTextureCubeMap->TopTexture() = _resourceManager.lock()->FindAsset<Texture>(document["albedo_top"].GetString());
			}

			if (document.HasMember("albedo_bottom") && document["albedo_bottom"].IsString())
			{
				std::string folderDirectory = document["albedo_bottom"].GetString();
				_albedoTextureCubeMap->BottomTexture() = _resourceManager.lock()->FindAsset<Texture>(document["albedo_bottom"].GetString());
			}

			if (document.HasMember("albedo_front") && document["albedo_front"].IsString())
			{
				std::string folderDirectory = document["albedo_front"].GetString();
				_albedoTextureCubeMap->FrontTexture() = _resourceManager.lock()->FindAsset<Texture>(document["albedo_front"].GetString());
			}

			if (document.HasMember("albedo_back") && document["albedo_back"].IsString())
			{
				std::string folderDirectory = document["albedo_back"].GetString();
				_albedoTextureCubeMap->BackTexture() = _resourceManager.lock()->FindAsset<Texture>(document["albedo_back"].GetString());
			}
		}

		glm::vec4& SkyboxMaterial::Colour() { return _colour; }
		std::shared_ptr<ShaderProgram>& SkyboxMaterial::GetShaderProgram() { return _shaderProgram; }
		std::shared_ptr<TextureCubeMap>& SkyboxMaterial::GetAlbedoTextureCubeMap() { return _albedoTextureCubeMap; }
	}
}