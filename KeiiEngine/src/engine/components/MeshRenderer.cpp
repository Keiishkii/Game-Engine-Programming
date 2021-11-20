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
#include "engine/resources/Material.h"
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
			int total = 0;
			for (int i = 0; i < _renderModel->TotalMaterialGroups(); i++)
			{
				std::shared_ptr<ResourceManagement::Material> material = _renderModel->GetMaterial(i);

				if (!material)
				{
					material = corePtr.lock()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/default_material.material");
				}

				std::shared_ptr<ResourceManagement::ShaderProgram> shaderProgram = material->GetShaderProgram();
				std::shared_ptr<ResourceManagement::Texture> albedoMap = material->GetAlbedoTexture();

				GLuint programID = 0;
				if (shaderProgram)
				{
					programID = shaderProgram->GetShaderID();
				}
				else
				{
					shaderProgram = corePtr.lock()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/default_shader_program.glsl");
					programID = shaderProgram->GetShaderID();
				}

				glUseProgram(programID);

				if (albedoMap) shaderProgram->UploadTextureMapToShader(albedoMap, "in_AbedoMap");

				GLint colourID = glGetUniformLocation(programID, "in_Colour");
				GLint modelMatrixID = glGetUniformLocation(programID, "in_Model");
				GLint viewingMatrixID = glGetUniformLocation(programID, "in_Veiwing");
				GLint projectionMatrixID = glGetUniformLocation(programID, "in_Projection");

				std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = _renderModel->GetPolygonMaterialGroup(i);

				glBindVertexArray(polygonMaterialGroup->VertexArrayID());

				glm::vec4 colour = material->GetColour();
				//std::cout << "Colour: [" << colour.x << ", " << colour.y << ", " << colour.z << ", " << colour.w << "]" << std::endl;

				glUniform4fv(colourID, 1, glm::value_ptr(colour));

				glm::mat4x4 modelMatrix = Transform().lock()->TransformationMatrix();
				glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

				glm::mat4x4 viewingMatrix = glm::inverse(activeCamera.lock()->Transform().lock()->TransformationMatrix());
				glUniformMatrix4fv(viewingMatrixID, 1, GL_FALSE, glm::value_ptr(viewingMatrix));

				glm::mat4x4 projectionMatrix = activeCamera.lock()->ProjectionMatrix();
				glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

				// Draw to the screen
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDrawArrays(GL_TRIANGLES, 0, polygonMaterialGroup->VertexCount());
				total += polygonMaterialGroup->VertexCount();
			}			
		}
	}
}