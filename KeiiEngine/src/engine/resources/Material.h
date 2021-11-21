#include <glm/vec4.hpp>
#include <glew.h>

#include "Resource.h"
#include "rapidjson/document.h"

using namespace rapidjson;

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture;
		struct ShaderProgram;
		struct Material : Resource
		{
		private:
			std::shared_ptr<ShaderProgram> _shaderProgram;
			std::shared_ptr<Texture> _albedoTexture, _normalTexture;

			glm::vec4 _colour = {1, 1, 1, 1};
		public:


		private:
			void AssignShader(const Document& document);
			void AssignColour(const Document& document);
			void AssignAlbedoTexture(const Document& document);
			void AssignNormalTexture(const Document& document);
		public:
			virtual void Load(const std::string& path) override;

			glm::vec4& Colour();
			std::shared_ptr<ShaderProgram>& GetShaderProgram();
			std::shared_ptr<Texture>& GetAlbedoTexture();
			std::shared_ptr<Texture>& GetNormalTexture();
		};
	}
}