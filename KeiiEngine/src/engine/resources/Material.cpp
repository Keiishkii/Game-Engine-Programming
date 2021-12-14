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
			std::string jsonString = ResourceManager::ReadText(resourcesDirectory + subPath);
			Document document = ResourceManager::ToJSON(jsonString);

			for (auto& materialProperty : document.GetObject())
			{
				std::string propertyName = materialProperty.name.GetString();

				if (document[propertyName.c_str()].IsFloat() || document[propertyName.c_str()].IsInt())
				{
					AssignProperty_Float(propertyName, document[propertyName.c_str()].GetFloat());
				}
				else if (document[propertyName.c_str()].IsArray())
				{
					const Value& array = document[propertyName.c_str()];
					if (array.Size() > 0)
					{
						if ((array[0].IsFloat() || array[0].IsInt()))
						{
							switch (array.Size())
							{
								case 2:
								{
									AssignProperty_Vec2(propertyName, glm::vec2(array[0].GetFloat(), array[1].GetFloat()));
								}break;
								case 3:
								{
									AssignProperty_Vec3(propertyName, glm::vec3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat()));
								}break;
								case 4:
								{
									AssignProperty_Vec4(propertyName, glm::vec4(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat(), array[3].GetFloat()));
								}break;
							}
						}
					}
				}
				else if (document[propertyName.c_str()].IsString())
				{
					std::string propertyContent = document[propertyName.c_str()].GetString();
					if (propertyContent.find(".glsl") != std::string::npos)
					{
						AssignProperty_ShaderProgram(propertyContent);
					}
					else if (propertyContent.find(".png") != std::string::npos)
					{
						AssignProperty_Texture(propertyName, propertyContent);
					}
				}
			}
		}

		void Material::AssignProperty_ShaderProgram(const std::string& resourcePath)
		{
			MaterialShader = _resourceManager.lock()->FindAsset<ShaderProgram>(resourcePath);
		}

		void Material::AssignProperty_Texture(const std::string& propertyKey, const std::string& resourcePath)
		{
			if (!Properties_Texture.count(propertyKey))
			{
				Properties_Texture.insert(std::pair < std::string, std::shared_ptr<Texture> > (propertyKey, _resourceManager.lock()->FindAsset<Texture>(resourcePath)));
			}
			else
			{
				Properties_Texture[propertyKey] = _resourceManager.lock()->FindAsset<Texture>(resourcePath);
			}
		}

		void Material::AssignProperty_Float(const std::string& propertyKey, float materialProperty)
		{
			if (!Properties_Float.count(propertyKey))
			{
				Properties_Float.insert(std::pair<std::string, float>(propertyKey, materialProperty));
			}
			else
			{
				Properties_Float[propertyKey] = materialProperty;
			}
		}

		void Material::AssignProperty_Vec2(const std::string& propertyKey, glm::vec2 materialProperty)
		{
			if (!Properties_Vec2.count(propertyKey))
			{
				Properties_Vec2.insert(std::pair<std::string, glm::vec2>(propertyKey, materialProperty));
			}
			else
			{
				Properties_Vec2[propertyKey] = materialProperty;
			}
		}

		void Material::AssignProperty_Vec3(const std::string& propertyKey, glm::vec3 materialProperty)
		{
			if (!Properties_Vec3.count(propertyKey))
			{
				Properties_Vec3.insert(std::pair<std::string, glm::vec3>(propertyKey, materialProperty));
			}
			else
			{
				Properties_Vec3[propertyKey] = materialProperty;
			}
		}

		void Material::AssignProperty_Vec4(const std::string& propertyKey, glm::vec4 materialProperty)
		{
			if (!Properties_Vec4.count(propertyKey))
			{
				Properties_Vec4.insert(std::pair<std::string, glm::vec4>(propertyKey, materialProperty));
			}
			else
			{
				Properties_Vec4[propertyKey] = materialProperty;
			}
		}
	}
}