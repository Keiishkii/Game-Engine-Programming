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
			std::weak_ptr<ShaderProgram> _shaderProgram;
			std::weak_ptr<Texture> _albedoTexture, _normalTexture;

			glm::vec4 _colour;
		public:


		private:
			void AssignShader(Document& document, GLuint& shaderProgramID);
			void AssignColour(Document& document);
			void AssignAlbedoTexture(Document& document, GLuint& shaderProgramID);
			void AssignNormalTexture(Document& document, GLuint& shaderProgramID);
		public:
			virtual void Load(std::string path) override;

			std::shared_ptr<ShaderProgram> GetShaderProgram();
			glm::vec4 GetColour();
			std::shared_ptr<Texture> GetAlbedoTexture();
			std::shared_ptr<Texture> GetNormalTexture();
		};
	}
}