#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "engine/Core.h"
#include "engine/resources/ResourceManager.h"
#include "engine/resources/ShaderProgram.h"
#include "engine/resources/Model.h"
#include "engine/graphics/PolygonMaterialGroup.h"
#include "engine/error-handling/Exception.h"

namespace Engine
{
	namespace Components
	{
		MeshRenderer::MeshRenderer(std::shared_ptr<ResourceManagement::Model> renderModel)
		{
			_renderModel = renderModel;
		}

		void MeshRenderer::Update() { }
		void MeshRenderer::PhysicsUpdate() { }

		//void MeshRenderer::Render(std::weak_ptr<Components::Camera>& activeCamera)
		void MeshRenderer::Render(std::weak_ptr<Components::Camera>& activeCamera)
		{
			for (int i = 0; i < _renderModel->TotalMaterialGroups(); i++)
			{
				GLuint programID = corePtr.lock()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/simpleprogram.glsl")->GetShaderID();

				GLint modelMatrixID = glGetUniformLocation(programID, "in_Model");
				GLint inverseVeiwingMatrixID = glGetUniformLocation(programID, "in_InverseVeiwing");
				GLint projectionMatrixID = glGetUniformLocation(programID, "in_Projection");

				
				glUseProgram(programID);

				glBindVertexArray(_renderModel->GetPolygonMaterialGroup(i)->VertexArrayID());

				glm::mat4x4 modelMatrix = Transform().lock()->TransformationMatrix();
				glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

				glm::mat4x4 viewingMatrix = glm::inverse(activeCamera.lock()->Transform().lock()->TransformationMatrix());
				glUniformMatrix4fv(inverseVeiwingMatrixID, 1, GL_FALSE, glm::value_ptr(viewingMatrix));

				glm::mat4x4 projectionMatrix = activeCamera.lock()->ProjectionMatrix();
				glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));



				std::cout << "MATRIX DATA: ------ " << std::endl;
				for (int j = 0; j < modelMatrix.length(); j++)
					std::cout << modelMatrix[j].x << ", " << modelMatrix[j].y << ", " << modelMatrix[j].z << ", " << modelMatrix[j].w << std::endl;



				// Draw to the screen
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDrawArrays(GL_TRIANGLES, 0, _renderModel->GetPolygonMaterialGroup(i)->VertexCount());
			}			
		}
	}
}