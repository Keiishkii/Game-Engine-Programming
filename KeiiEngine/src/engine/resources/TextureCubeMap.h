#include <glew.h>
#include <vector>

#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct TextureCubeMap : Resource
		{
		private:
			GLuint _textureID = 0;
			int _width, _height;

			std::vector<std::string> _faceSuffexes = {"_front", "_back", "_top", "_bottom", "_left", "_right"};

			unsigned char* _rightTexture;
			unsigned char* _leftTexture;
			unsigned char* _topTexture;
			unsigned char* _bottomTexture;
			unsigned char* _frontTexture;
			unsigned char* _backTexture;
		public:


		private:
		public:
			virtual void Load(const std::string& path) override;

			GLuint GetCubeMapTextureID();
		};
	}
}