#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>
#include <string>
#include <memory>

namespace Engine
{
	namespace Graphics
	{
		struct VertexBuffer;
		struct VertexArray
		{
		private:
			bool _dirty = false;
			GLuint _id = 0;

			std::map<std::string, std::shared_ptr<VertexBuffer>> _vertexBuffers;
		public:


		private:
		public:
			VertexArray();

			GLuint GetID();
			int GetVertexCount();


			void SetVertexCount(int _vertexCount);
			void SetBuffer(std::string _buffer, std::shared_ptr<VertexBuffer> _content);
		};
	}
}