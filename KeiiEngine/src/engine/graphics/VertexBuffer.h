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
			bool _dirty = false;
			GLuint _ID = 0;

			std::vector<GLfloat> _data;
			int _components = 0;
		public:


		private:
		public:
			VertexBuffer();

			GLuint GetID();
			int VertexBuffer::GetComponentSize();
			std::vector<GLfloat>& GetData();

			void Add(const glm::vec2& value);
			void Add(const glm::vec3& value);
			void Add(const glm::vec4& value);
		};
	}
}