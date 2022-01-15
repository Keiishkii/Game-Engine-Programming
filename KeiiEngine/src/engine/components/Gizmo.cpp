#include "Gizmo.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include <iostream>
#include <math.h>

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
			_gizmoTexture = gizmoTexture;
			_gizmoShaderProgram = Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/gizmo_shader_program.glsl");
			_gizmoVertexArrayObject = std::make_shared<Graphics::VertexArray>();

			_colour = glm::vec3(1, 1, 1);

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

			_gizmoVertexArrayObject->SetBuffer("in_Position", positionBuffer);
			_gizmoVertexArrayObject->SetBuffer("in_Normal", normalBuffer);
			_gizmoVertexArrayObject->SetBuffer("in_TextureUV", textureUVBuffer);
		}

		void Gizmo::Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix)
		{
			#if DEBUG
				_gizmoShaderProgram->UseShader();


				glm::vec3 translation, scale, skew;	glm::quat rotation;	glm::vec4 perspective;
				glm::decompose(transformationMatrix, scale, rotation, translation, skew, perspective);

				rotation = glm::conjugate(rotation);

				std::shared_ptr<Components::Transform> transform = Transform();
				glm::mat4x4 modelMatrix = 
					glm::translate(glm::identity<glm::mat4x4>(), transform->Position()) *
					glm::mat4_cast(glm::quatLookAt(glm::normalize(transform->Position() - translation), glm::vec3(0, 1, 0)) * glm::quat(glm::vec3(0, 0, M_PI))) *
					glm::scale(glm::identity<glm::mat4x4>(), scale);


				_gizmoShaderProgram->SetUniform("in_GizmoTexture", _gizmoTexture);
				_gizmoShaderProgram->SetUniform("in_Colour", _colour);

				_gizmoShaderProgram->SetUniform("in_Model", modelMatrix);
				_gizmoShaderProgram->SetUniform("in_Veiwing", glm::inverse(transformationMatrix));
				_gizmoShaderProgram->SetUniform("in_Projection", projectionMatrix);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				_gizmoShaderProgram->DrawTriangles(_gizmoVertexArrayObject->GetID(_gizmoShaderProgram), 6);

				_gizmoShaderProgram->StopUsingShader();
			#endif
		}
	}
}