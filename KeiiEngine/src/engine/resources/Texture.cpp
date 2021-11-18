#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "glm/stb_image.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void Texture::Load(std::string path)
		{
			width = 0, height = 0;
			_texture = stbi_load("models/xenoblade/images/def_shulk_001_col.png", &width, &height, NULL, 4);
		}
	}
}																	