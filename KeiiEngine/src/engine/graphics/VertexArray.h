#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>
#include <string>
#include <memory>

namespace Engine
{
	namespace ResourceManagement { struct ShaderProgram; }
	namespace Graphics
	{
		struct VertexBuffer;
		struct VertexArray
		{
		private:
			std::map<GLuint, GLuint> _vaoIDs;
			std::map<GLuint, bool> _shaderDirtyStates;
			std::map<std::string, std::shared_ptr<VertexBuffer>> _vertexBuffers;
		public:


		private:
		public:
			void SetBuffer(const std::string& _buffer, const std::shared_ptr<VertexBuffer>& _content);
			GLuint GetID(std::shared_ptr<ResourceManagement::ShaderProgram> shaderProgram);
		};
	}
}