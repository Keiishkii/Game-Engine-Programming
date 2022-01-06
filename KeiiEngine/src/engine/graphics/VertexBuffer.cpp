#include "VertexBuffer.h"
#include "engine/error-handling/Exception.h"


using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace Graphics
	{
		VertexBuffer::VertexBuffer()
		{
			glGenBuffers(1, &_ID);

			if (!_ID) [[unlikely]]
			{
				throw Exception("Failed to generate 'Vertex Buffer' ID");
			}
		}

		GLuint VertexBuffer::GetID()
		{
			if (_dirty) [[unlikely]]
			{
				glBindBuffer(GL_ARRAY_BUFFER, _ID);
				glBufferData(GL_ARRAY_BUFFER, sizeof(_data.at(0)) * _data.size(), &_data.at(0), GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				_dirty = false;
			}

			return _ID;
		}

		void VertexBuffer::Add(const glm::vec2& _value)
		{
			if (_components != 0 && _components != 2)
			{
				throw Exception("Failed to add value to vertex list due to it being of size 2 and not " + _components);
			}

			_data.push_back(_value.x);
			_data.push_back(_value.y);

			_dirty = true;

			_components = 2;
		}

		void VertexBuffer::Add(const glm::vec3& _value)
		{
			if (_components != 0 && _components != 3)
			{
				throw Exception("Failed to add value to vertex list due to it being of size 3 and not " + _components);
			}

			_data.push_back(_value.x);
			_data.push_back(_value.y);
			_data.push_back(_value.z);

			_dirty = true;

			_components = 3;
		}

		void VertexBuffer::Add(const glm::vec4& _value)
		{
			if (_components != 0 && _components != 4)
			{
				throw Exception("Failed to add value to vertex list due to it being of size 4 and not " + _components);
			}

			_data.push_back(_value.x);
			_data.push_back(_value.y);
			_data.push_back(_value.z);
			_data.push_back(_value.w);

			_dirty = true;

			_components = 4;
		}

		int VertexBuffer::GetComponentSize() { return _components; }
		std::vector<GLfloat>& VertexBuffer::GetData() { return _data; }
	}
}