#include <memory>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "engine/core.h"
#include "engine/resources/ResourceManager.h"
#include "GraphicsManager.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "engine/error-handling/Exception.h"
#include "engine/components/Camera.h"
#include "engine/components/Transform.h"
#include "engine/resources/ShaderProgram.h"
#include "engine/resources/SkyboxMaterial.h"

namespace Engine
{
	namespace Graphics
	{
		void GraphicsManager::Initialise(std::shared_ptr<Engine::Core> core)
		{
			_core = core;
		}

		void GraphicsManager::CreateRenderBuffer(GLuint& framebufferID, GLuint& framebufferColourTextureID, GLuint& frameBufferDepthTextureID, int width, int height)
		{
			glGenFramebuffers(1, &framebufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);


			glGenTextures(1, &framebufferColourTextureID);
			glBindTexture(GL_TEXTURE_2D, framebufferColourTextureID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferColourTextureID, 0);


			glGenRenderbuffers(1, &frameBufferDepthTextureID);
			glBindRenderbuffer(GL_RENDERBUFFER, frameBufferDepthTextureID);

			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frameBufferDepthTextureID);

			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
		}

		void GraphicsManager::RenderSkybox(std::shared_ptr<ResourceManagement::SkyboxMaterial> skybox, const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix)
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

			glBindVertexArray(Skybox()->GetID());

			glm::vec4 colour = skybox->Colour();
			glUniform4fv(colourID, 1, glm::value_ptr(colour));


			glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(transformationMatrix));

			glm::mat4x4 viewingMatrix = glm::mat4x4(glm::mat3x3(glm::inverse(transformationMatrix)));
			glUniformMatrix4fv(viewingMatrixID, 1, GL_FALSE, glm::value_ptr(viewingMatrix));

			glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


			glDrawArrays(GL_TRIANGLES, 0, 36);

			glDepthFunc(GL_LESS);
		}

		std::shared_ptr<Graphics::VertexArray> GraphicsManager::Quad()
		{
			if (!_quad)
			{
				_quad = std::make_shared<Graphics::VertexArray>();

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

				_quad->SetBuffer("Vertex Position Buffer", positionBuffer);
				_quad->SetBuffer("Texture UV Buffer", textureUVBuffer);
				_quad->SetBuffer("Vertex Normal Buffer", normalBuffer);
			}

			return _quad;
		}

		std::shared_ptr<Graphics::VertexArray> GraphicsManager::Skybox()
		{
			if (!_skybox)
			{
				_skybox = std::make_shared<Graphics::VertexArray>();

				std::shared_ptr<Graphics::VertexBuffer> positionBuffer = std::make_shared<Graphics::VertexBuffer>();
				{
					positionBuffer->Add(glm::vec3(-5000,  5000,  5000));
					positionBuffer->Add(glm::vec3( 5000,  5000,  5000));
					positionBuffer->Add(glm::vec3( 5000, -5000,  5000));
					positionBuffer->Add(glm::vec3( 5000, -5000,  5000));
					positionBuffer->Add(glm::vec3( 5000, -5000, -5000));
					positionBuffer->Add(glm::vec3(-5000, -5000, -5000));
														  
					positionBuffer->Add(glm::vec3(-5000, -5000,  5000));
					positionBuffer->Add(glm::vec3(-5000, -5000, -5000));
					positionBuffer->Add(glm::vec3(-5000,  5000, -5000));
					positionBuffer->Add(glm::vec3( 5000,  5000, -5000));
					positionBuffer->Add(glm::vec3(-5000,  5000, -5000));
					positionBuffer->Add(glm::vec3(-5000, -5000, -5000));
														  
					positionBuffer->Add(glm::vec3( 5000,  5000,  5000));
					positionBuffer->Add(glm::vec3( 5000,  5000, -5000));
					positionBuffer->Add(glm::vec3( 5000, -5000, -5000));
					positionBuffer->Add(glm::vec3(-5000,  5000,  5000));
					positionBuffer->Add(glm::vec3(-5000,  5000, -5000));
					positionBuffer->Add(glm::vec3( 5000,  5000, -5000));
														  
					positionBuffer->Add(glm::vec3(-5000,  5000,  5000));
					positionBuffer->Add(glm::vec3( 5000, -5000,  5000));
					positionBuffer->Add(glm::vec3(-5000, -5000,  5000));
					positionBuffer->Add(glm::vec3( 5000, -5000,  5000));
					positionBuffer->Add(glm::vec3(-5000, -5000, -5000));
					positionBuffer->Add(glm::vec3(-5000, -5000,  5000));
														  
					positionBuffer->Add(glm::vec3(-5000, -5000,  5000));
					positionBuffer->Add(glm::vec3(-5000,  5000, -5000));
					positionBuffer->Add(glm::vec3(-5000,  5000,  5000));
					positionBuffer->Add(glm::vec3( 5000,  5000, -5000));
					positionBuffer->Add(glm::vec3(-5000, -5000, -5000));
					positionBuffer->Add(glm::vec3( 5000, -5000, -5000));
														  
					positionBuffer->Add(glm::vec3( 5000,  5000,  5000));
					positionBuffer->Add(glm::vec3( 5000, -5000, -5000));
					positionBuffer->Add(glm::vec3( 5000, -5000,  5000));
					positionBuffer->Add(glm::vec3(-5000,  5000,  5000));
					positionBuffer->Add(glm::vec3( 5000,  5000, -5000));
					positionBuffer->Add(glm::vec3( 5000,  5000,  5000));
				}
				std::shared_ptr<Graphics::VertexBuffer> textureUVBuffer = std::make_shared<Graphics::VertexBuffer>();
				{
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 1, 0));

					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 1, 0));

					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 1, 0));

					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 1, 0));

					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 0, 0));
					textureUVBuffer->Add(glm::vec3(1, 1, 0));
					textureUVBuffer->Add(glm::vec3(0, 1, 0));

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

					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));

					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));

					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));

					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));

					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
					normalBuffer->Add(glm::vec3(0, 0, 0));
				}

				_skybox->SetBuffer("Vertex Position Buffer", positionBuffer);
				_skybox->SetBuffer("Texture UV Buffer", textureUVBuffer);
				_skybox->SetBuffer("Vertex Normal Buffer", normalBuffer);
			}

			return _skybox;
		}


		std::shared_ptr<ResourceManagement::ShaderProgram> GraphicsManager::GetPostProcessingShader()
		{
			if (!_postProcessingShader) [[unlikely]]
			{
				_postProcessingShader = Core()->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/buffer_shader_shader.glsl");
			}

			return _postProcessingShader;
		}
		void GraphicsManager::SetPostProcessingShader(std::shared_ptr<ResourceManagement::ShaderProgram> postProcessingShader)
		{
			_postProcessingShader = postProcessingShader;
		}

		std::shared_ptr<Engine::Core> GraphicsManager::Core() { return _core.lock(); }
	}
}