#include "glm/stb_image.h"

#include "Texture.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void Texture::Load(const std::string& path)
		{
			_width = 0, _height = 0;
			_texture = stbi_load(path.c_str(), &_width, &_height, NULL, 4);

			if (!_texture)
				throw ErrorHandling::Exception("Failed to load texture");
		}

		GLuint Texture::GetTextureID()
		{
			if (!_textureID)
			{
				glGenTextures(1, &_textureID);

				if (!_textureID)
				{
					throw ErrorHandling::Exception("Failed to create a texture ID for the albedo texture.");
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, _textureID);

					// Upload the image data to the bound texture unit in the GPU
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
						GL_UNSIGNED_BYTE, _texture);

					// Free the loaded data because we now have a copy on the GPU
					free(_texture);
					glGenerateMipmap(GL_TEXTURE_2D);
				}
			}

			return _textureID;
		}

		int Texture::GetWidth()	{ return _width; }
		int Texture::GetHeight() { return _height; }
		unsigned char* Texture::GetTexture() { return _texture; }
	}
}																	