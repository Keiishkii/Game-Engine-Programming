#include <glew.h>
#include <string>

#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		/**	The Texture is a type of resource, it acts as the engines storage for .png files, and converts them to a GLuint for use in OpenGL.  	*/
		struct Texture : Resource
		{
		private:
			GLuint _textureID = 0;

			int _channelCount;
			int _width, _height;
			GLubyte* _texture;
			std::string _path;
		public:


		private:
		public:
			void CreateTexture(int width, int height, int channels, GLubyte* texture);

			~Texture();
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;

			GLuint GetTextureID();

			int& ChannelCount();
			int& Width();
			int& Height();
			unsigned char*& TextureData();
		};
	}
}