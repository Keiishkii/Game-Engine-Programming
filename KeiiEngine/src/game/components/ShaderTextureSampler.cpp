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
		std::shared_ptr<ResourceManagement::Texture> texture = Core()->RenderTexture();

		std::string directory = Core()->ResourceManager()->GetResourceDirectory() + "- - RuntimeTextureGeneration\\PNG_WrittenFile.png";
		stbi_write_png(directory.c_str(), texture->Width(), texture->Height(), texture->ChannelCount(), texture->TextureData(), texture->Width() * texture->ChannelCount());
	}
}

/*

 - Z Fighting Test for distance
 - - - Depth Buffer Precision
 - - - Floating point depth formats

 - Dodgy Scaling
 - Shadows or PBR (both need to do the texture saving)
 - - - LearnOpenGL -> Unreal showcase


To Do:
 ----------------------- Get Rid of console outs (MAKING EVERYTHING SLOW TO LOAD)
 - Render to Texture
 - Render to CubeMaps (might just be worth doing 6 textures)
 - Auto Generate a list of manually placed CubeMaps
 - Send all textures to the graphics card.
 - Look into interpelation between them.
 - Add to lighting calculation (WRITE LIGHTING CALCULATION)


  - - - https://stackoverflow.com/questions/61153680/how-to-use-stbi-write-png-to-write-image-pixel-data-to-a-png-file
  
 */