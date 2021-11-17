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

		GLuint VertexArray::GetID()
		{
			if (_dirty)
			{
				glBindVertexArray(_id);


				std::shared_ptr<VertexBuffer> vertexPositionBuffer = _vertexBuffers["Vertex Position Buffer"];
				glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer->getID());
				glVertexAttribPointer(0, vertexPositionBuffer->GetComponentSize(), GL_FLOAT, GL_FALSE, vertexPositionBuffer->GetComponentSize() * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(0); 
				
				std::shared_ptr<VertexBuffer> vertexNormalBuffer = _vertexBuffers["Vertex Normal Buffer"];
				glBindBuffer(GL_ARRAY_BUFFER, vertexNormalBuffer->getID());
				glVertexAttribPointer(1, vertexNormalBuffer->GetComponentSize(), GL_FLOAT, GL_FALSE, vertexNormalBuffer->GetComponentSize() * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(1);

				std::shared_ptr<VertexBuffer> textureUVBuffer = _vertexBuffers["Texture UV Buffer"];
				glBindBuffer(GL_ARRAY_BUFFER, textureUVBuffer->getID());
				glVertexAttribPointer(2, textureUVBuffer->GetComponentSize(), GL_FLOAT, GL_FALSE, textureUVBuffer->GetComponentSize() * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(2);
				

				// Reset the state
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				_dirty = false;
			}

			return _id;
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