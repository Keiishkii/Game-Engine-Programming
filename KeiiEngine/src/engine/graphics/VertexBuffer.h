#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace Engine
{
	namespace Graphics
	{
		struct VertexBuffer
		{
		private:
			GLuint _ID = 0;
			int _components = 0;
			std::vector<GLfloat> _data;
			bool _dirty = false;
		public:


		private:
		public:
			VertexBuffer();

			GLuint getID();
			int VertexBuffer::GetComponentSize();
			std::vector<GLfloat> GetData();

			void Add(const glm::vec2& value);
			void Add(const glm::vec3& value);
			void Add(const glm::vec4& value);
		};
	}
}