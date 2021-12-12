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
		_material = Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/shulk/clothing.material");
	}

	void ShaderTextureSampler::Update()
	{
		if (Input()->KeyHeld(Input()->F))
		{
			std::shared_ptr<ResourceManagement::TextureCubeMap> cubeMap = Core()->ResourceManager()->Create<ResourceManagement::TextureCubeMap>();
			cubeMap->GenerateCubeMap(glm::vec3(0, 0, 2));

			//Scene()->Skybox()->GetAlbedoTextureCubeMap() = cubeMap;

			/*
			std::string directory = Core()->ResourceManager()->GetResourceDirectory() + "- - RuntimeTextureGeneration\\PNG_WrittenFile";
			std::string extension = ".png";

			stbi_write_png((directory + "_Right" + extension).c_str() , cubeMap->RightTexture()->Width(), cubeMap->RightTexture()->Height(), cubeMap->RightTexture()->ChannelCount(), cubeMap->RightTexture()->TextureData(), cubeMap->RightTexture()->Width() * cubeMap->RightTexture()->ChannelCount());
			stbi_write_png((directory + "_Left" + extension).c_str()  , cubeMap->LeftTexture()->Width(), cubeMap->LeftTexture()->Height(), cubeMap->LeftTexture()->ChannelCount(), cubeMap->LeftTexture()->TextureData(), cubeMap->LeftTexture()->Width() * cubeMap->LeftTexture()->ChannelCount());
			stbi_write_png((directory + "_Top" + extension).c_str()   , cubeMap->TopTexture()->Width(), cubeMap->TopTexture()->Height(), cubeMap->TopTexture()->ChannelCount(), cubeMap->TopTexture()->TextureData(), cubeMap->TopTexture()->Width() * cubeMap->TopTexture()->ChannelCount());
			stbi_write_png((directory + "_Bottom" + extension).c_str(), cubeMap->BottomTexture()->Width(), cubeMap->BottomTexture()->Height(), cubeMap->BottomTexture()->ChannelCount(), cubeMap->BottomTexture()->TextureData(), cubeMap->BottomTexture()->Width() * cubeMap->BottomTexture()->ChannelCount());
			stbi_write_png((directory + "_Front" + extension).c_str() , cubeMap->FrontTexture()->Width(), cubeMap->FrontTexture()->Height(), cubeMap->FrontTexture()->ChannelCount(), cubeMap->FrontTexture()->TextureData(), cubeMap->FrontTexture()->Width() * cubeMap->FrontTexture()->ChannelCount());
			stbi_write_png((directory + "_Back" + extension).c_str()  , cubeMap->BackTexture()->Width(), cubeMap->BackTexture()->Height(), cubeMap->BackTexture()->ChannelCount(), cubeMap->BackTexture()->TextureData(), cubeMap->BackTexture()->Width() * cubeMap->BackTexture()->ChannelCount());
			*/
		}

		if (Input()->KeyHeld(Input()->E))
		{
			if (_material)
			{
				if (Input()->KeyHeld(Input()->LCNTRL))
					_material->Roughness() = std::max(0.0f, _material->Roughness() - 0.01f);
				else
					_material->Roughness() = std::min(1.0f, _material->Roughness() + 0.01f);

				std::cout << "Roughness: " << _material->Roughness() << std::endl;
				std::cout << "Metallic:  " << _material->Metallic() << std::endl;
			}
		}

		if (Input()->KeyHeld(Input()->R))
		{
			if (_material)
			{
				if (Input()->KeyHeld(Input()->LCNTRL))
					_material->Metallic() = std::max(0.0f, _material->Metallic() - 0.01f);
				else
					_material->Metallic() = std::min(1.0f, _material->Metallic() + 0.01f);

				std::cout << "Roughness: " << _material->Roughness() << std::endl;
				std::cout << "Metallic:  " << _material->Metallic() << std::endl;
			}
		}
	}
}

/*
 - Shadows or PBR (both need to do the texture saving)
 - - - LearnOpenGL -> Unreal showcase


To Do:
 ----------------------- Get Rid of console outs (MAKING EVERYTHING SLOW TO LOAD)
 ---------- Render to Texture
 ---------- Render to CubeMaps (might just be worth doing 6 textures)
 - Auto Generate a list of manually placed CubeMaps
 - Send all textures to the graphics card.
 - Look into interpelation between them.
 - Add to lighting calculation (WRITE LIGHTING CALCULATION)


  - - - https://stackoverflow.com/questions/61153680/how-to-use-stbi-write-png-to-write-image-pixel-data-to-a-png-file
  
 */