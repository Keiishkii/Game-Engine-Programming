#include <glm/vec4.hpp>
#include <glew.h>

#include "Resource.h"
#include "rapidjson/document.h"

using namespace rapidjson;

namespace Engine
{
	namespace ResourceManagement
	{
		struct TextureCubeMap;
		struct ShaderProgram;
		struct SkyboxMaterial : Resource
		{
		private:
			std::shared_ptr<ShaderProgram> _shaderProgram;
			std::shared_ptr<TextureCubeMap> _albedoTextureCubeMap;

			glm::vec4 _colour = {1, 1, 1, 1};
		public:


		private:
			void AssignShader(const Document& document);
			void AssignColour(const Document& document);
			void AssignAlbedoTextureCubeMap(const Document& document);
		public:
			virtual void Load(const std::string& path) override;

			glm::vec4& Colour();
			std::shared_ptr<ShaderProgram>& GetShaderProgram();
			std::shared_ptr<TextureCubeMap>& GetAlbedoTextureCubeMap();
		};
	}
}