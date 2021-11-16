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
				for (std::map<std::string, std::shared_ptr<VertexBuffer>>::iterator it = _vertexBuffers.begin(); it != _vertexBuffers.end(); it++, bufferID++)
				{
					std::shared_ptr<VertexBuffer> buffer = it->second;

					glBindBuffer(GL_ARRAY_BUFFER, buffer->getID());
					glVertexAttribPointer(bufferID, buffer->GetComponentSize(), GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
					glEnableVertexAttribArray(bufferID);
				}

				// Reset the state
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				_dirty = false;
			}

			return _id;
		}

		std::shared_ptr<VertexBuffer> VertexArray::GetVertexBuffer(std::string key)
		{
			std::shared_ptr<VertexBuffer> buffer = NULL;

			if (!_vertexBuffers.count(key))
			{
				throw ErrorHandling::Exception("The VertexBuffer map does not contain any buffers using the key " + key + ".");
			}
			else
			{
				buffer = _vertexBuffers[key];
			}

			return buffer;
		}

		void VertexArray::SetBuffer(std::string _buffer, std::shared_ptr<VertexBuffer> _content)
		{
			if (!_vertexBuffers.count(_buffer))
			{
				_vertexBuffers.insert(std::pair<std::string, std::shared_ptr<VertexBuffer>>(_buffer, _content));
			}
			else
			{
				_vertexBuffers[_buffer] = _content;
			}

			_dirty = true;
		}
	}
}