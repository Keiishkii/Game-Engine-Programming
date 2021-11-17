#include "VertexArray.h"
#include "VertexBuffer.h"

#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace Graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &_id);

			if (!_id)
			{
				throw ErrorHandling::Exception("Failed to generate an ID for the 'Vertex Array'.");
			}
		}

		void VertexArray::SetVertexCount(int _vertexCount) { _vertexCount = _vertexCount; }
		int VertexArray::GetVertexCount() { return _vertexCount; }

		GLuint VertexArray::GetID()
		{
			if (_dirty)
			{
				glBindVertexArray(_id);

				int bufferID = 0;
				for (std::map<std::string, VertexBuffer>::iterator it = _vertexBuffers.begin(); it != _vertexBuffers.end(); it++, bufferID++)
				{
					VertexBuffer buffer = it->second;

					glBindBuffer(GL_ARRAY_BUFFER, buffer.getID());
					glVertexAttribPointer(bufferID, buffer.GetComponentSize(), GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
					glEnableVertexAttribArray(bufferID);
				}

				// Reset the state
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				_dirty = false;
			}

			return _id;
		}

		void VertexArray::SetBuffer(std::string _buffer, VertexBuffer& _content)
		{
			if (!_vertexBuffers.count(_buffer))
			{
				_vertexBuffers.insert(std::pair<std::string, VertexBuffer>(_buffer, _content));
			}
			else
			{
				_vertexBuffers[_buffer] = _content;
			}

			_dirty = true;
		}
	}
}