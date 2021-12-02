#include <glew.h>
#include <string>

#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture : Resource
		{
		private:
			GLuint _textureID = 0;

			int _numberOfChannels;
			int _width, _height;
			GLubyte* _texture;
			std::string _path;
		public:


		private:
		public:
			~Texture();
			virtual void Load(const std::string& path) override;

			GLuint GetTextureID();

			int GetChannelCount();
			int GetWidth();
			int GetHeight();
			unsigned char* GetTexture();
		};
	}
}