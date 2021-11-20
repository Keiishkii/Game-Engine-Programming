#include <glew.h>

#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture : Resource
		{
		private:
			GLuint _textureID = 0;

			int _width, _height;
			unsigned char* _texture;
		public:


		private:
		public:
			virtual void Load(std::string path) override;

			GLuint GetTextureID();

			int GetWidth();
			int GetHeight();
			unsigned char* GetTexture();
		};
	}
}