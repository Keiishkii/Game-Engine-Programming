#include "VertexArray.h"
#include "VertexBuffer.h"

#include "engine/resources/ShaderProgram.h"
#include "engine/error-handling/Exception.h"

using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace Graphics
	{
		GLuint VertexArray::GetID(std::shared_ptr<ResourceManagement::ShaderProgram> shaderProgram)
		{
			GLuint shaderID = shaderProgram->GetShaderID();
			if (!_shaderDirtyStates.count(shaderID) || _shaderDirtyStates[shaderID]) [[unlikely]]
			{
				if (!_vaoIDs.count(shaderID)) [[unlikely]]
				{
					GLuint vaoID;
					glGenVertexArrays(1, &vaoID);

					if (!vaoID)
					{
						throw Exception("Failed to generate an ID for the 'Vertex Array'.");
					}
					else
					{
						_vaoIDs.insert(std::pair<GLuint, GLuint>(shaderID, vaoID));
					}
				}

				glBindVertexArray(_vaoIDs[shaderID]);



				std::map<std::string, std::shared_ptr<VertexBuffer>>::iterator iterator;
				for (iterator = _vertexBuffers.begin(); iterator != _vertexBuffers.end(); iterator++)
				{
					GLint attributePositionID = shaderProgram->GetAttributeID(iterator->first);
					if (attributePositionID >= 0)
					{
						glBindBuffer(GL_ARRAY_BUFFER, iterator->second->GetID());

						glVertexAttribPointer(attributePositionID, iterator->second->GetComponentSize(), GL_FLOAT, GL_FALSE, iterator->second->GetComponentSize() * sizeof(GLfloat), (void*)0);
						glEnableVertexAttribArray(attributePositionID);
					}
				}

				// Reset the state
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				_shaderDirtyStates[shaderID] = false;
			}

			return _vaoIDs[shaderID];
		}

		void VertexArray::SetBuffer(const std::string& _buffer, const std::shared_ptr<VertexBuffer>& _content)
		{
			if (!_vertexBuffers.count(_buffer))
			{
				_vertexBuffers.insert(std::pair<std::string, std::shared_ptr<VertexBuffer>>(_buffer, _content));
			}
			else
			{
				_vertexBuffers[_buffer] = _content;
			}

			std::map<GLuint, bool>::iterator iterator;
			for (iterator = _shaderDirtyStates.begin(); iterator != _shaderDirtyStates.end(); iterator++)
			{
				iterator->second = true;
			}
		}
	}
}