#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Engine
{
	namespace Graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &id);

			if (!id)
			{
				throw std::exception();
			}
		}

		void VertexArray::setVertexCount(int _vertexCount)
		{
			vertexCount = _vertexCount;
		}

		GLuint VertexArray::getID()
		{
			if (dirty)
			{
				glBindVertexArray(id);

				//VertexPositions
				glBindBuffer(GL_ARRAY_BUFFER, vertexPositions->getID());
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(0);

				//TexturesPositions
				glBindBuffer(GL_ARRAY_BUFFER, textureUVs->getID());
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(1);

				//Normals
				glBindBuffer(GL_ARRAY_BUFFER, vertexNormals->getID());
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(2);

				//Tangents
				glBindBuffer(GL_ARRAY_BUFFER, vertexTangents->getID());
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(3);

				//Bitangents
				glBindBuffer(GL_ARRAY_BUFFER, vertexBitangents->getID());
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(3);

				// Reset the state
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				dirty = false;
			}

			return id;
		}

		void VertexArray::setBuffer(std::string _buffer, std::shared_ptr<VertexBuffer> _content)
		{
			if (_buffer._Equal("VertexPositions"))
			{
				vertexPositions = _content;
			}
			else if (_buffer._Equal("TextureUVs"))
			{
				textureUVs = _content;
			}
			else if (_buffer._Equal("VertexNormals"))
			{
				vertexNormals = _content;
			}
			else if (_buffer._Equal("VertexTangents"))
			{
				vertexTangents = _content;
			}
			else if (_buffer._Equal("VertexBitangents"))
			{
				vertexBitangents = _content;
			}

			dirty = true;
		}
	}
}