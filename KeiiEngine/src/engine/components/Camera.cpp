#include <iostream>
#include <glew.h>

#include "Camera.h"
#include "engine/Core.h"
#include "engine/Scene.h"
#include "Transform.h"
#include "engine/entity.h"
#include "engine/resources/SkyboxMaterial.h"
#include "engine/resources/Model.h"
#include "engine/resources/TextureCubeMap.h"
#include "engine/resources/ShaderProgram.h"
#include "engine/resources/ResourceManager.h"
#include "engine/graphics/PolygonMaterialGroup.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace Components
	{
		void Camera::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			Scene()->_cameraList.push_back(std::dynamic_pointer_cast<Camera>(self));
			_skyboxCube = Core()->ResourceManager()->FindAsset<ResourceManagement::Model>("- models/skybox.fbx");
		}
	
		void Camera::GenerateNewProjectionMatrix(float windowWidth, float windowHeight, float fieldOfView)
		{
			_projectionMatrix = glm::perspective(glm::radians(fieldOfView), (float)windowWidth / (float)windowHeight, 0.25f, 5000.f);
		}

		void Camera::RenderSkybox()
		{
			std::shared_ptr<ResourceManagement::SkyboxMaterial> skybox = Scene()->Skybox();
			if (skybox)
			{
				glDepthFunc(GL_LEQUAL);

				std::shared_ptr<ResourceManagement::ShaderProgram> shader = skybox->GetShaderProgram();
				GLuint programID = shader->GetShaderID();
				glUseProgram(programID);

				shader->UploadTextureMapToShader(skybox->GetAlbedoTextureCubeMap(), "in_Skybox");

				GLint colourID = glGetUniformLocation(programID, "in_Colour");
				GLint modelMatrixID = glGetUniformLocation(programID, "in_Model");
				GLint viewingMatrixID = glGetUniformLocation(programID, "in_Veiwing");
				GLint projectionMatrixID = glGetUniformLocation(programID, "in_Projection");

				std::shared_ptr<Graphics::PolygonMaterialGroup> cubeMaterialGroup = _skyboxCube->GetPolygonMaterialGroup(0);

				glBindVertexArray(cubeMaterialGroup->VertexArrayID());

				glm::vec4 colour = skybox->Colour();
				glUniform4fv(colourID, 1, glm::value_ptr(colour));

				glm::mat4x4 modelMatrix = Transform()->TransformationMatrix();
				glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

				glm::mat4x4 viewingMatrix = glm::mat4x4(glm::mat3x3(glm::inverse(Transform()->TransformationMatrix())));
				glUniformMatrix4fv(viewingMatrixID, 1, GL_FALSE, glm::value_ptr(viewingMatrix));

				glm::mat4x4 projectionMatrix = ProjectionMatrix();
				glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

				glDrawArrays(GL_TRIANGLES, 0, cubeMaterialGroup->VertexCount());

				glDepthFunc(GL_LESS);
			}
		}

		glm::mat4x4& Camera::ProjectionMatrix() { return _projectionMatrix; }
	}
}