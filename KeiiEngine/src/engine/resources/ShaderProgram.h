#include <string>
#include <map>
#include <memory>
#include <glew.h>

#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		struct Texture;
		struct TextureCubeMap;
		struct ShaderProgram : Resource
		{
		private:
			GLuint _shaderProgramID;
			std::map<std::string, GLuint> _textureMapSampleIDs;
		public:


		private:
			void GenerateVertexShader(std::string shader, GLuint& shaderID);
			void GenerateFragmentShader(std::string shader, GLuint& shaderID);
			void GenerateShaderAttributes(GLuint programID, const std::string& path);

			GLuint GetTextureSampleID(const std::string& sample);
		public:
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;
			void UploadTextureMapToShader(const std::shared_ptr<Texture>& textureMap, const std::string& sample);
			void UploadTextureMapToShader(const std::shared_ptr<TextureCubeMap>& textureMap, const std::string& sample);

			GLuint& GetShaderID();
		};
	}
}