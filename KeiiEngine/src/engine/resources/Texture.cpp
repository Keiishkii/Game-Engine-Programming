#include "glm/stb_image.h"
#include "glm/stb_image_write.h"
#include <iostream>

#include "Texture.h"
#include "ResourceManager.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void Texture::CreateTexture(int width, int height, int channelCount, GLubyte* texture)
		{
			_width = width;	_height = height;
			_channelCount = channelCount;

			_texture = texture;
		}

		void Texture::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			std::string path = resourcesDirectory + subPath;
			_path = path;

			_channelCount = 4;
			_width = 0, _height = 0;

			_texture = stbi_load(path.c_str(), &_width, &_height, NULL, _channelCount);

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
					glGenerateMipmap(GL_TEXTURE_2D);
				}
			}

			return _textureID;
		}

		Texture::~Texture()
		{
			if (_textureID)
				glDeleteTextures(1, &_textureID);
			
			free(_texture);
		}

		int& Texture::ChannelCount()	{ return _channelCount; }
		int& Texture::Width()	{ return _width; }
		int& Texture::Height() { return _height; }
		unsigned char*& Texture::TextureData() { return _texture; }
	}
}																	