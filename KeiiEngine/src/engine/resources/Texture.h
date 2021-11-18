#include <glew.h>

#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture : Resource
		{
		private:
			GLuint _textureID;

			int width, height;
			unsigned char* _texture;
		public:


		private:
		public:
			virtual void Load(std::string path) override;
		};
	}
}