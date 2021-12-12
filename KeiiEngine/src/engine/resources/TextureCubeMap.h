#include <glew.h>
#include <vector>
#include "glm/glm.hpp"

#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture;
		struct TextureCubeMap : Resource
		{
		private:
			GLuint _textureID = 0;
			GLuint _textureConvolutionID = 0;
			std::vector<std::string> _faceSuffexes = {"right", "left", "top", "bottom", "front", "back"};
						
			std::shared_ptr<Texture> _rightTexture;
			std::shared_ptr<Texture> _leftTexture;
			std::shared_ptr<Texture> _topTexture;
			std::shared_ptr<Texture> _bottomTexture;
			std::shared_ptr<Texture> _frontTexture;
			std::shared_ptr<Texture> _backTexture;
		public:


		private:
		public:
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;
			void GenerateCubeMap(glm::vec3 position);
			void GenerateCubeMapConvolution();

			~TextureCubeMap();

			GLuint GetCubeMapTextureID();
			GLuint GetCubeMapConvolutionTextureID();

			std::shared_ptr<Texture>& RightTexture();
			std::shared_ptr<Texture>& LeftTexture();
			std::shared_ptr<Texture>& TopTexture();
			std::shared_ptr<Texture>& BottomTexture();
			std::shared_ptr<Texture>& FrontTexture();
			std::shared_ptr<Texture>& BackTexture();
		};
	}
}