#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>

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
			glm::vec3 translation, scale, skew;
			glm::quat rotation;
			glm::vec4 perspective;
			glm::decompose(transformationMatrix, scale, rotation, translation, skew, perspective);

			std::vector<std::weak_ptr<Components::Light>> lights = Scene()->Lights();
			int lightCount = lights.size();

			glm::vec3* positions = new glm::vec3[lightCount];
			glm::vec3* colours = new glm::vec3[lightCount];
			float* intensitys = new float[lightCount];

			for (int i = 0; i < lightCount; i++)
			{
				positions[i] = lights[i].lock()->Transform()->Position();
				colours[i] = lights[i].lock()->Colour();
				intensitys[i] = lights[i].lock()->Intensity();
			}


			for (int i = 0; i < _renderModel->TotalMaterialGroups(); i++)
			{
				std::shared_ptr<ResourceManagement::Material> material = _renderModel->GetMaterial(i);
				std::shared_ptr<Graphics::PolygonMaterialGroup> polygonMaterialGroup = _renderModel->GetPolygonMaterialGroup(i);

				std::shared_ptr<ResourceManagement::ShaderProgram> shaderProgram = material->MaterialShader;		

				shaderProgram->UseShader();


				shaderProgram->SetMaterialUniforms(material);

				shaderProgram->SetUniform("in_Model", Transform()->TransformationMatrix());
				shaderProgram->SetUniform("in_Veiwing", glm::inverse(transformationMatrix));
				shaderProgram->SetUniform("in_Projection", projectionMatrix);

				shaderProgram->SetUniform("in_ViewPosition", translation);

				shaderProgram->SetUniform("in_LightCount", lightCount);
				shaderProgram->SetUniform("in_LightPositions", &positions[0], lightCount);
				shaderProgram->SetUniform("in_LightColours", &colours[0], lightCount);
				shaderProgram->SetUniform("in_LightIntensitys", &intensitys[0], lightCount);


				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				shaderProgram->DrawTriangles(polygonMaterialGroup, shaderProgram);


				shaderProgram->StopUsingShader();
			}			

			delete[lightCount] positions;
			delete[lightCount] colours;
			delete[lightCount] intensitys;
		}
	}
}