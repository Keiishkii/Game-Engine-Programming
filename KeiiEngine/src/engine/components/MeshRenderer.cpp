#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Light.h"
#include "engine/Core.h"
#include "engine/Scene.h"
#include "engine/resources/ResourceManager.h"
#include "engine/resources/ShaderProgram.h"
#include "engine/resources/Material.h"
#include "engine/resources/Model.h"
#include "engine/graphics/PolygonMaterialGroup.h"
#include "engine/error-handling/Exception.h"

using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace Components
	{
		void MeshRenderer::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity, std::shared_ptr<ResourceManagement::Model> renderModel)
		{
			_renderModel = renderModel;
		}

		void MeshRenderer::Render(const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix)
		{
			for (int i = 0; i < _renderModel->TotalMaterialGroups(); i++)
			{
				std::shared_ptr<ResourceManagement::Material> material = _renderModel->GetMaterial(i);

				if (!material)
				{
					material = Core()->ResourceManager()->FindAsset<ResourceManagement::Material>("- materials/default_material.material");
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
					shaderProgram = Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/default_shader_program.glsl");
					programID = shaderProgram->GetShaderID();
				}

				glUseProgram(programID);

				if (albedoMap) shaderProgram->UploadTextureMapToShader(albedoMap, "in_AlbedoMap");

				GLint colourID = glGetUniformLocation(programID, "in_Colour");
				GLint modelMatrixID = glGetUniformLocation(programID, "in_Model");
				GLint viewingMatrixID = glGetUniformLocation(programID, "in_Veiwing");
				GLint projectionMatrixID = glGetUniformLocation(programID, "in_Projection");

				GLint lightCountID = glGetUniformLocation(programID, "in_LightCount");
				GLint lightPositionArrayID = glGetUniformLocation(programID, "in_LightPositions");
				GLint lightColourArrayID = glGetUniformLocation(programID, "in_LightColours");
				GLint lightIntensityArrayID = glGetUniformLocation(programID, "in_LightIntensitys");



				std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = _renderModel->GetPolygonMaterialGroup(i);

				glBindVertexArray(polygonMaterialGroup->VertexArrayID());

				glm::vec4 colour = material->Colour();

				glUniform4fv(colourID, 1, glm::value_ptr(colour));

				glm::mat4x4 modelMatrix = Transform()->TransformationMatrix();
				glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

				glm::mat4x4 viewingMatrix = glm::inverse(transformationMatrix);
				glUniformMatrix4fv(viewingMatrixID, 1, GL_FALSE, glm::value_ptr(viewingMatrix));

				glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

				
				std::vector<std::weak_ptr<Components::Light>> lights = Scene()->Lights();
				int lightCount = lights.size();

				glUniform1f(lightCountID, lightCount);
				glUniform3fv(lightPositionArrayID, lightCount, glm::value_ptr(lights[0].lock()->Transform()->Position()));
				glUniform3fv(lightColourArrayID, lightCount, glm::value_ptr(lights[0].lock()->Colour()));
				glUniform1fv(lightIntensityArrayID, lightCount, &lights[0].lock()->Intensity());

				// Draw to the screen
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDrawArrays(GL_TRIANGLES, 0, polygonMaterialGroup->VertexCount());
			}			
		}
	}
}