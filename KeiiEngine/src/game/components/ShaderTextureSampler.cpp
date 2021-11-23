#include "ShaderTextureSampler.h"

#include <iostream>

namespace Game
{
	void ShaderTextureSampler::Start()
	{

	}

	void ShaderTextureSampler::Update()
	{
		std::cout << "Updating" << std::endl;
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
 - Get Rid of console outs (MAKING EVERYTHING SLOW TO LOAD)
 - Render to Texture
 - Render to CubeMaps (might just be worth doing 6 textures)
 - Auto Generate a list of manually placed CubeMaps
 - Send all textures to the graphics card.
 - Look into interpelation between them.
 - Add to lighting calculation (WRITE LIGHTING CALCULATION)


  - - - https://stackoverflow.com/questions/61153680/how-to-use-stbi-write-png-to-write-image-pixel-data-to-a-png-file
  
 */