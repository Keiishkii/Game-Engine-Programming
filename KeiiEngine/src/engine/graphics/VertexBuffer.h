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
			GLuint id = 0;
			int components = 0;
			std::vector<GLfloat> data;
			bool dirty = false;
		public:


		private:
		public:
			VertexBuffer();

			GLuint getID();
			std::vector<GLfloat> getData() { return data; };

			void add(const glm::vec2& value);
			void add(const glm::vec3& value);
			void add(const glm::vec4& value);
		};
	}
}