#include "engine/KeiiEngine.h"

#include "ShaderTextureSampler.h"
#include "glm/stb_image.h"
#include "glm/stb_image_write.h"

#include <iostream>
#include <vector>

namespace Game
{
	void ShaderTextureSampler::Start()
	{
		/*
		std::shared_ptr<ResourceManagement::Texture> texture = Core()->ResourceManager()->FindAsset<ResourceManagement::Texture>("- textures/shulk/eye.png");

		GLubyte* textureData = new GLubyte[texture->Width() * texture->Height() * texture->ChannelCount()];

		std::string directory = Core()->ResourceManager()->GetResourceDirectory() + "- - RuntimeTextureGeneration\\outputTest.png";
		//std::cout << "New: " << _texture << std::endl;
		//std::cout << "Old: " << texture << std::endl;

		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

		stbi_write_png(directory.c_str(), texture->Width(), texture->Height(), texture->ChannelCount(), textureData, texture->Width() * texture->ChannelCount());
		free(textureData);*/
	}

	void ShaderTextureSampler::Update()
	{
		if (Input()->KeyHeld(Input()->F))
		{
			std::shared_ptr<ResourceManagement::TextureCubeMap> cubeMap = Core()->ResourceManager()->Create<ResourceManagement::TextureCubeMap>();
			cubeMap->GenerateCubeMap(glm::vec3(0, 0, 2));

			Scene()->Skybox()->GetAlbedoTextureCubeMap() = cubeMap;

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
		/*
		std::shared_ptr<ResourceManagement::Texture> texture = Core()->RenderTexture();

		std::string directory = Core()->ResourceManager()->GetResourceDirectory() + "- - RuntimeTextureGeneration\\PNG_WrittenFile.png";
		stbi_write_png(directory.c_str(), texture->Width(), texture->Height(), texture->ChannelCount(), texture->TextureData(), texture->Width() * texture->ChannelCount());
		*/
	}
}

/*
 - Shadows or PBR (both need to do the texture saving)
 - - - LearnOpenGL -> Unreal showcase


To Do:
 ----------------------- Get Rid of console outs (MAKING EVERYTHING SLOW TO LOAD)
 ---------- Render to Texture
 - Render to CubeMaps (might just be worth doing 6 textures)
 - Auto Generate a list of manually placed CubeMaps
 - Send all textures to the graphics card.
 - Look into interpelation between them.
 - Add to lighting calculation (WRITE LIGHTING CALCULATION)


  - - - https://stackoverflow.com/questions/61153680/how-to-use-stbi-write-png-to-write-image-pixel-data-to-a-png-file
  
 */