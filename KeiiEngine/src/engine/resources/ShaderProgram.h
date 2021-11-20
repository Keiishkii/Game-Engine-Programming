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
		struct ShaderProgram : Resource
		{
		private:
			GLuint _shaderProgramID;
			std::map<std::string, GLuint> _textureMapSampleIDs;
		public:


		private:
			void GenerateVertexShader(std::string shader, GLuint& shaderID);
			void GenerateFragmentShader(std::string shader, GLuint& shaderID);
			void GenerateShaderAttributes(GLuint programID, std::string path);

			GLuint GetTextureSampleID(std::string sample);
		public:
			virtual void Load(std::string path) override;

			GLuint& GetShaderID();
			void UploadTextureMapToShader(std::shared_ptr<Texture> textureMap, std::string sample);
		};
	}
}