#include <glm/glm.hpp>
#include <glew.h>
#include <map>

#include "Resource.h"
#include "rapidjson/document.h"

using namespace rapidjson;

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture;
		struct ShaderProgram;

		/**	The Material is a type of resource, it is used to read in material data from files. This includes texture data and shaders.  	*/
		struct Material : Resource
		{
		private:
			std::shared_ptr<Texture> _albedoTexture, _normalTexture;

			glm::vec4 _colour = {1, 1, 1, 1};
			float _roughness = 0;
			float _metallic = 0;
		public:
			std::shared_ptr<ShaderProgram> MaterialShader;

			std::map<std::string, std::shared_ptr<Texture>> Properties_Texture;
			std::map<std::string, float> Properties_Float;
			std::map<std::string, glm::vec2> Properties_Vec2;
			std::map<std::string, glm::vec3> Properties_Vec3;
			std::map<std::string, glm::vec4> Properties_Vec4;


		private:
			void AssignProperty_ShaderProgram(const std::string& resourcePath);
			void AssignProperty_Texture(const std::string& propertyKey, const std::string& resourcePath);
			void AssignProperty_Float(const std::string& propertyKey, float materialProperty);
			void AssignProperty_Vec2(const std::string& propertyKey, glm::vec2 materialProperty);
			void AssignProperty_Vec3(const std::string& propertyKey, glm::vec3 materialProperty);
			void AssignProperty_Vec4(const std::string& propertyKey, glm::vec4 materialProperty);
		public:
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;
		};
	}
}