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
		int width = 256, height = 256;
		int channelNumber = 3;

		std::vector<char> pixelList;

		for (int i = 0; i < width * height; i++)
		{
			pixelList.push_back('a');
			pixelList.push_back('a');
			pixelList.push_back('a');
			//pixelList.push_back('a');
		}

		std::string directory = Core()->ResourceManager()->GetResourceDirectory() + "texture_1.png";
		std::cout << "Written to directory: " << directory << std::endl;

		char* texture;
		glBindTexture(GL_TEXTURE_2D, 1);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		stbi_write_png(directory.c_str(), width, height, channelNumber, pixelList.data(), width * channelNumber);
		*/
	}

	void ShaderTextureSampler::Update()
	{

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