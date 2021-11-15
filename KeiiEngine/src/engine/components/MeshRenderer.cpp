#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "MeshRenderer.h"
#include "engine/Core.h"
#include "engine/resources/ResourceManager.h"
#include "engine/resources/ShaderProgram.h"

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

		void MeshRenderer::Render() 
		{
			GLuint programID = corePtr.lock()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/simpleprogram.glsl")->GetShaderID();

			GLint modelID = glGetUniformLocation(programID, "in_Model");
			GLint projectionID = glGetUniformLocation(programID, "in_Projection");
			GLint invVeiwingID = glGetUniformLocation(programID, "in_InverseVeiwing");

			glm::mat4x4 model(1.0f);
			model = glm::translate(model, glm::vec3(0, 0, -2));

			glUseProgram(programID);
			glBindVertexArray(getVertexArrayObject()->getID());

			glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(_projection));
			glUniformMatrix4fv(invVeiwingID, 1, GL_FALSE, glm::value_ptr(_veiwing));

			// Draw to the screen
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDrawArrays(GL_TRIANGLES, 0, getVertexArrayObject()->getVertexCount());
		}
	}
}