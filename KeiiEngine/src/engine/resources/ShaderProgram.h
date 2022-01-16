#include <string>
#include <map>
#include <memory>
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Resource.h"

namespace Engine
{
	namespace Graphics { struct PolygonMaterialGroup; }
	namespace ResourceManagement
	{
		struct Texture;
		struct Material;
		struct TextureCubeMap;

		/**	The ShaderProgram is a type of resource, it is used to load shader text files and convert the fragment and vertex code to a singlular shader program that can be used with OpenGL.  	*/
		struct ShaderProgram : Resource
		{
		private:
			std::string _name;

			GLuint _shaderProgramID;

			std::map<std::string, GLint> _uniformIDMap;
			std::map<std::string, GLint> _attributeIDMap;
		public:


		private:
			void GenerateVertexShader(const std::string& subPath, const std::string& shader, GLuint& shaderID);
			void GenerateFragmentShader(const std::string& subPath, const std::string& shader, GLuint& shaderID);
		public:
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;

			void UseShader();
			void StopUsingShader();

			void SetMaterialUniforms(std::shared_ptr<Material> material);

			#pragma region Set Uniforms
			void SetUniform(std::string unifromLocation, float data);
			void SetUniform(std::string unifromLocation, glm::vec2 data);
			void SetUniform(std::string unifromLocation, glm::vec3 data);
			void SetUniform(std::string unifromLocation, glm::vec4 data);
			void SetUniform(std::string unifromLocation, glm::mat4x4 data);
			void SetUniform(std::string unifromLocation, std::shared_ptr<Texture> data);
			void SetUniform(std::string unifromLocation, std::shared_ptr<TextureCubeMap> data);

			void SetUniform(std::string unifromLocation, float data[], int count);
			void SetUniform(std::string unifromLocation, glm::vec2 data[], int count);
			void SetUniform(std::string unifromLocation, glm::vec3 data[], int count);
			void SetUniform(std::string unifromLocation, glm::vec4 data[], int count);
			void SetUniform(std::string unifromLocation, glm::mat4x4 data[], int count);
			#pragma endregion

			#pragma region Draw Triangles
			void DrawTriangles(std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup, std::shared_ptr<ShaderProgram> shaderProgram);
			void DrawTriangles(GLuint meshID, int vertexCount);
			#pragma endregion

			GLuint GetShaderID();
			GLint GetUniformID(const std::string& sample);
			GLint GetAttributeID(const std::string& sample);
		};
	}
}