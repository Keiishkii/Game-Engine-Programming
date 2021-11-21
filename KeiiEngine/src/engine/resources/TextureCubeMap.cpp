#include "glm/stb_image.h"

#include "TextureCubeMap.h"
#include "engine/error-handling/Exception.h"
#include <iostream>
#include <vector>

namespace Engine
{
	namespace ResourceManagement
	{
		void TextureCubeMap::Load(const std::string& path)
		{
			std::string pathWithoutExtension = path.substr(0, path.size() - 4);
			std::string pathExtension = path.substr(path.size() - 4);

			std::string rightFacePath = pathWithoutExtension + _faceSuffexes[5] + pathExtension;
			_rightTexture = stbi_load(rightFacePath.c_str(), &_width, &_height, NULL, 0);
			if (!_rightTexture)
				throw ErrorHandling::Exception("Failed to load right texture of cube map");

			std::string leftFacePath = pathWithoutExtension + _faceSuffexes[4] + pathExtension;
			_leftTexture = stbi_load(leftFacePath.c_str(), &_width, &_height, NULL, 0);
			if (!_leftTexture)
				throw ErrorHandling::Exception("Failed to load left texture of cube map");

			std::string topFacePath = pathWithoutExtension + _faceSuffexes[2] + pathExtension;
			_topTexture = stbi_load(topFacePath.c_str(), &_width, &_height, NULL, 0);
			if (!_topTexture)
				throw ErrorHandling::Exception("Failed to load top texture of cube map");

			std::string bottomFacePath = pathWithoutExtension + _faceSuffexes[3] + pathExtension;
			_bottomTexture = stbi_load(bottomFacePath.c_str(), &_width, &_height, NULL, 0);
			if (!_bottomTexture)
				throw ErrorHandling::Exception("Failed to load bottom texture of cube map");

			std::string frontFacePath = pathWithoutExtension + _faceSuffexes[0] + pathExtension;
			_frontTexture = stbi_load(frontFacePath.c_str(), &_width, &_height, NULL, 0);
			if (!_frontTexture)
				throw ErrorHandling::Exception("Failed to load front texture of cube map");

			std::string backFacePath = pathWithoutExtension + _faceSuffexes[1] + pathExtension;
			_backTexture = stbi_load(backFacePath.c_str(), &_width, &_height, NULL, 0);
			if (!_backTexture)
				throw ErrorHandling::Exception("Failed to load back texture of cube map");
		}

		GLuint TextureCubeMap::GetCubeMapTextureID()
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
					glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _rightTexture);
					free(_rightTexture);

					glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _leftTexture);
					free(_leftTexture);

					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _topTexture);
					free(_topTexture);

					glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _bottomTexture);
					free(_bottomTexture);

					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _frontTexture);
					free(_frontTexture);

					glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _backTexture);
					free(_backTexture);

					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				}
			}

			return _textureID;
		}
	}
}																	