#include "VertexBuffer.h"

namespace Engine
{
	namespace Graphics
	{
		VertexBuffer::VertexBuffer()
		{
			glGenBuffers(1, &id);

			if (!id)
			{
				throw std::exception();
			}
		}

		GLuint VertexBuffer::getID()
		{
			if (dirty)
			{
				glBindBuffer(GL_ARRAY_BUFFER, id);
				glBufferData(GL_ARRAY_BUFFER, sizeof(data.at(0)) * data.size(), &data.at(0), GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				dirty = false;
			}

			return id;
		}

		void VertexBuffer::add(const glm::vec2& _value)
		{
			if (components != 0 && components != 2)
			{
				throw std::exception();
			}

			data.push_back(_value.x);
			data.push_back(_value.y);

			dirty = true;

			components = 2;
		}

		void VertexBuffer::add(const glm::vec3& _value)
		{
			if (components != 0 && components != 3)
			{
				throw std::exception();
			}

			data.push_back(_value.x);
			data.push_back(_value.y);
			data.push_back(_value.z);

			dirty = true;

			components = 3;
		}

		void VertexBuffer::add(const glm::vec4& _value)
		{
			if (components != 0 && components != 4)
			{
				throw std::exception();
			}

			data.push_back(_value.x);
			data.push_back(_value.y);
			data.push_back(_value.z);
			data.push_back(_value.w);

			dirty = true;

			components = 4;
		}
	}
}