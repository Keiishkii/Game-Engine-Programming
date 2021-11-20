#define STB_IMAGE_IMPLEMENTATION
#include "glm/stb_image.h"

#include "Texture.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void Texture::Load(std::string path)
		{
			_width = 0, _height = 0;
			_texture = stbi_load(path.c_str(), &_width, &_height, NULL, 4);

			if (!_texture)
			{
				throw ErrorHandling::Exception("Failed to load texture");
			}
		}

		int Texture::GetWidth()	{ return _width; }
		int Texture::GetHeight() { return _height; }
		unsigned char* Texture::GetTexture() { return _texture; }
	}
}																	