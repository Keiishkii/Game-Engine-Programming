#include <memory>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "stb/stb_image_write.h"

#include "engine/core.h"
#include "engine/Scene.h"
#include "engine/resources/ResourceManager.h"
#include "GraphicsManager.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "engine/components/Camera.h"
#include "engine/components/Transform.h"
#include "engine/resources/ShaderProgram.h"
#include "engine/resources/SkyboxMaterial.h"
#include "engine/resources/Texture.h"
#include "engine/error-handling/Exception.h"

using Engine::ErrorHandling::Exception;
namespace Engine
{
	namespace Graphics
	{
		void GraphicsManager::Initialise(std::shared_ptr<Engine::Core> core, int windowWidth, int windowHeight)
		{
			_core = core;

			SDLInitialisation(windowWidth, windowHeight);
			SetPostProcessingShader(core->ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/- Post Processing/buffer_shader_shader.glsl"));
		}

		void GraphicsManager::SDLInitialisation(int windowWidth, int windowHeight)
		{
			_window = std::make_shared<SDL_Window*>(SDL_CreateWindow("Keii Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
			
			//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

			if (!SDL_GL_CreateContext(*_window))
			{
				throw Exception("Failed to create window context");
			}
			else
			{
				int i = 0;
				SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &i);

				if (SDL_SetRelativeMouseMode(SDL_TRUE))
				{
					throw Exception("Failed to set relative mouse position");
				}
				else
				{
					if (glewInit() != GLEW_OK)
					{
						throw Exception("Failed to initialise GLEW");
					}
				}
			}
		}



		void GraphicsManager::RenderFrame(std::shared_ptr<Scene> activeScene)
		{
			int width = 0, height = 0;
			
			SDL_GetWindowSize(*_window, &width, &height);
			glViewport(0, 0, width, height);


			std::shared_ptr<Components::Camera> mainCamera = activeScene->MainCamera();
			if (mainCamera) [[likely]]
			{
				mainCamera->GenerateNewProjectionMatrix(width, height, 45);
				GLuint renderTexture = activeScene->RenderSceneToTextureBuffer(mainCamera->Transform()->TransformationMatrix(), mainCamera->ProjectionMatrix(), width, height);
				
				glClearColor(0.2f, 0.4f, 0.5f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				glDisable(GL_DEPTH_TEST);

				_postProcessingShader->UseShader();


				glBindTexture(GL_TEXTURE_2D, renderTexture);
				_postProcessingShader->DrawTriangles(Quad()->GetID(_postProcessingShader), 6);


				_postProcessingShader->StopUsingShader();

				glDeleteTextures(1, &renderTexture);
			}
			else
			{
				Exception("There is no main camera").Print();
			}

			SDL_GL_SwapWindow(*_window);
		}

		void GraphicsManager::RenderSkybox(std::shared_ptr<ResourceManagement::SkyboxMaterial> skybox, const glm::mat4x4& transformationMatrix, const glm::mat4x4& projectionMatrix)
		{
			if (skybox)
			{
				std::shared_ptr<ResourceManagement::ShaderProgram> shaderProgram = skybox->GetShaderProgram();

				if (shaderProgram)
				{
					glDepthFunc(GL_LEQUAL);

					shaderProgram->UseShader();


					shaderProgram->SetUniform("in_Albedo", skybox->GetAlbedoTextureCubeMap());

					shaderProgram->SetUniform("in_Colour", skybox->Colour());

					shaderProgram->SetUniform("in_Veiwing", glm::mat4x4(glm::mat3x3(glm::inverse(transformationMatrix))));
					shaderProgram->SetUniform("in_Projection", projectionMatrix);

					shaderProgram->DrawTriangles(Skybox()->GetID(shaderProgram), 36);


					shaderProgram->StopUsingShader();

					glDepthFunc(GL_LESS);
				}
			}
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

				_quad->SetBuffer("in_Position",	 positionBuffer);
				_quad->SetBuffer("in_Normal",	 normalBuffer);
				_quad->SetBuffer("in_TextureUV", textureUVBuffer);
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
					positionBuffer->Add(glm::vec3(-1,  1,  1));
					positionBuffer->Add(glm::vec3( 1,  1,  1));
					positionBuffer->Add(glm::vec3( 1, -1,  1));
					positionBuffer->Add(glm::vec3( 1, -1,  1));
					positionBuffer->Add(glm::vec3( 1, -1, -1));
					positionBuffer->Add(glm::vec3(-1, -1, -1));
														  
					positionBuffer->Add(glm::vec3(-1, -1,  1));
					positionBuffer->Add(glm::vec3(-1, -1, -1));
					positionBuffer->Add(glm::vec3(-1,  1, -1));
					positionBuffer->Add(glm::vec3( 1,  1, -1));
					positionBuffer->Add(glm::vec3(-1,  1, -1));
					positionBuffer->Add(glm::vec3(-1, -1, -1));
														  
					positionBuffer->Add(glm::vec3( 1,  1,  1));
					positionBuffer->Add(glm::vec3( 1,  1, -1));
					positionBuffer->Add(glm::vec3( 1, -1, -1));
					positionBuffer->Add(glm::vec3(-1,  1,  1));
					positionBuffer->Add(glm::vec3(-1,  1, -1));
					positionBuffer->Add(glm::vec3( 1,  1, -1));
														  
					positionBuffer->Add(glm::vec3(-1,  1,  1));
					positionBuffer->Add(glm::vec3( 1, -1,  1));
					positionBuffer->Add(glm::vec3(-1, -1,  1));
					positionBuffer->Add(glm::vec3( 1, -1,  1));
					positionBuffer->Add(glm::vec3(-1, -1, -1));
					positionBuffer->Add(glm::vec3(-1, -1,  1));
														  
					positionBuffer->Add(glm::vec3(-1, -1,  1));
					positionBuffer->Add(glm::vec3(-1,  1, -1));
					positionBuffer->Add(glm::vec3(-1,  1,  1));
					positionBuffer->Add(glm::vec3( 1,  1, -1));
					positionBuffer->Add(glm::vec3(-1, -1, -1));
					positionBuffer->Add(glm::vec3( 1, -1, -1));
														  
					positionBuffer->Add(glm::vec3( 1,  1,  1));
					positionBuffer->Add(glm::vec3( 1, -1, -1));
					positionBuffer->Add(glm::vec3( 1, -1,  1));
					positionBuffer->Add(glm::vec3(-1,  1,  1));
					positionBuffer->Add(glm::vec3( 1,  1, -1));
					positionBuffer->Add(glm::vec3( 1,  1,  1));
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

				_skybox->SetBuffer("in_Position",	positionBuffer);
				_skybox->SetBuffer("in_Normal",		normalBuffer);
				_skybox->SetBuffer("in_TextureUV",	textureUVBuffer);
			}

			return _skybox;
		}

		void GraphicsManager::SetPostProcessingShader(std::shared_ptr<ResourceManagement::ShaderProgram> postProcessingShader)
		{
			_postProcessingShader = postProcessingShader;
		}

		std::shared_ptr<Engine::Core> GraphicsManager::Core() { return _core.lock(); }

		GraphicsManager::~GraphicsManager()
		{
			SDL_DestroyWindow(*_window);
			SDL_Quit();
		}
	}
}