#include "Gizmo.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <iostream>

#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "engine/Core.h"
#include "engine/resources/Texture.h"
#include "engine/resources/ShaderProgram.h"
#include "engine/resources/ResourceManager.h"

#include "engine/graphics/VertexBuffer.h"
#include "engine/graphics/VertexArray.h"

#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace Components
	{
		void Gizmo::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity, std::shared_ptr<ResourceManagement::Texture> gizmoTexture)
		{
			#if _DEBUG
				_gizmoTexture = gizmoTexture;
				_gizmoShaderProgram = Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/gizmo_shader_program.glsl");
				_gizmoVertexArrayObject = std::make_shared<Graphics::VertexArray>();

				std::shared_ptr<Graphics::VertexBuffer> positionBuffer = std::make_shared<Graphics::VertexBuffer>();
				{
					positionBuffer->Add(glm::vec3(-1, -1, 0));
					positionBuffer->Add(glm::vec3(1, -1, 0));
					positionBuffer->Add(glm::vec3(1, 1, 0));
					positionBuffer->Add(glm::vec3(-1, -1, 0));
					positionBuffer->Add(glm::vec3(1, 1, 0));
					positionBuffer->Add(glm::vec3(-1, 1, 0));
				}
				std::shared_ptr<Graphics::VertexBuffer> textureUVBuffer = std::make_shared<Graphics::VertexBuffer>();
				{
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 1, 0));
				}
				std::shared_ptr<Graphics::VertexBuffer> normalBuffer = std::make_shared<Graphics::VertexBuffer>();
				{
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
				}
			#endif
		}

		void Gizmo::Render(const std::shared_ptr<Components::Camera>& activeCamera)
		{
			#if _DEBUG
				GLuint programID = _gizmoShaderProgram->GetShaderID();
				glUseProgram(programID);

				if (_gizmoTexture) _gizmoShaderProgram->UploadTextureMapToShader(_gizmoTexture, "in_GizmoTexture");

				GLint colourID = glGetUniformLocation(programID, "in_Colour");
				GLint modelMatrixID = glGetUniformLocation(programID, "in_Model");
				GLint viewingMatrixID = glGetUniformLocation(programID, "in_Veiwing");
				GLint projectionMatrixID = glGetUniformLocation(programID, "in_Projection");


				glBindVertexArray(_gizmoVertexArrayObject->GetID());

				glUniform4fv(colourID, 1, glm::value_ptr(_colour));


				std::cout << "Gizmo Position:		{" << Transform()->Position().x << ",	" << Transform()->Position().y << ",	" << Transform()->Position().z << "}" << std::endl;
				glm::mat4x4 modelMatrix = Transform()->TransformationMatrix();
				glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

				glm::mat4x4 viewingMatrix = glm::inverse(activeCamera->Transform()->TransformationMatrix());
				glUniformMatrix4fv(viewingMatrixID, 1, GL_FALSE, glm::value_ptr(viewingMatrix));

				glm::mat4x4 projectionMatrix = activeCamera->ProjectionMatrix();
				glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

				// Draw to the screen
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			#endif
		}
	}
}