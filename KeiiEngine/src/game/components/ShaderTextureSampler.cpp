#include "engine/KeiiEngine.h"

#include "ShaderTextureSampler.h"
#include "glm/stb_image.h"
#include "glm/stb_image_write.h"

#include <iostream>
#include <vector>
#include <cmath>

namespace Game
{
	void ShaderTextureSampler::Start()
	{
		_shaders.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/- PBR/shader_program_PBR-Torranec-Sparrow-Model.glsl"));
		_shaders.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/- PBR/shader_program_PBR.glsl"));

		activeShader = 0;
		std::cout << "Shader Selected: [" << _shaders[activeShader]->GetName() << "]" << std::endl;

		_materials.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/monado/red_metal.material"));
		_materials.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/monado/red_metal_core.material"));
		_materials.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/monado/glow.material"));
		_materials.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/monado/gold.material"));
		_materials.push_back(Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/monado/dark_gold.material"));

		activeMaterialSelection = 0;
		std::cout << "Material Selected: [" << _materials[activeMaterialSelection]->GetName() << "]" << std::endl;

		_propertyNames = {"in_Roughness", "in_Metallic", "in_Shininess", "in_SpecularWeight"};
		
		activeProperty = 0;
		std::cout << "Material Property Set: [" << _propertyNames[activeProperty] << "]" << std::endl;
	}

	void ShaderTextureSampler::Update()
	{
		if (Input()->KeyDown(Input()->F))
		{
			activeProperty++;

			if (activeProperty >= _propertyNames.size())
				activeProperty = 0;

			std::cout << "Material Property Set: [" << _propertyNames[activeProperty] << "]" << std::endl;
		}

		if (Input()->KeyDown(Input()->V))
		{
			activeMaterialSelection++;

			if (activeMaterialSelection >= _materials.size())
				activeMaterialSelection = 0;

			std::cout << "Material Property Set: [" << _materials[activeMaterialSelection]->GetName() << "]" << std::endl;
		}

		if (Input()->KeyDown(Input()->G))
		{
			activeShader++;

			if (activeShader >= _shaders.size())
				activeShader = 0;

			for (int i = 0; i < _materials.size(); i++)
			{
				_materials[i]->MaterialShader = _shaders[activeShader];
			}

			std::cout << "Material Property Set: [" << _shaders[activeShader]->GetName() << "]" << std::endl;
		}




		if (Input()->KeyHeld(Input()->R))
		{
			std::string propertyName = _propertyNames[activeProperty];
			if (_materials[activeMaterialSelection]->Properties_Float.count(propertyName))
			{
				_materials[activeMaterialSelection]->Properties_Float[propertyName] = std::min(1.0f, _materials[activeMaterialSelection]->Properties_Float[propertyName] + 0.001f);
				std::cout << propertyName <<  " = " << _materials[activeMaterialSelection]->Properties_Float[propertyName] << std::endl;
			}
		}

		if (Input()->KeyHeld(Input()->E))
		{
			std::string propertyName = _propertyNames[activeProperty];
			if (_materials[activeMaterialSelection]->Properties_Float.count(propertyName))
			{
				_materials[activeMaterialSelection]->Properties_Float[propertyName] = std::max(0.0f, _materials[activeMaterialSelection]->Properties_Float[propertyName] - 0.001f);
				std::cout << propertyName << " = " << _materials[activeMaterialSelection]->Properties_Float[propertyName] << std::endl;
			}
		}
	}
}