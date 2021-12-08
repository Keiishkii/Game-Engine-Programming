#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <glew.h>

#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Inputs.h"
#include "Entity.h"
#include "components/Camera.h"
#include "components/Transform.h"
#include "error-handling/Debugger.h"
#include "error-handling/Exception.h"
#include "graphics/PolygonMaterialGroup.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderProgram.h"
#include "resources/Model.h"
#include "resources/Texture.h"

using namespace Engine::ErrorHandling;
using namespace Engine::ResourceManagement;

namespace Engine
{
	std::shared_ptr<Core> Core::Initialise(int FPS, int fixedFPS)
	{
		std::shared_ptr<Core> core = std::make_shared<Core>();

		core->_self = core;
		core->_debugger = std::make_shared<ErrorHandling::Debugger>();
		core->_resources = std::make_shared<ResourceManagement::ResourceManager>();
		core->_resources->Initialise(core->_resources, core);

		core->_timeManager = std::make_shared<Engine::TimeManager>(FPS, fixedFPS);
		core->_inputManager = std::make_shared<Engine::InputManager>();

		core->SDLInitialisation();
		core->RenderBufferInitialisation();

		return core;
	}

	void Core::SDLInitialisation()
	{
		_window = std::make_shared<SDL_Window*>(SDL_CreateWindow("Keii Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 2000, 1200, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));

		try
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			
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
		catch (Exception e)
		{
			e.Print();
		}
	}

	void Core::RenderBufferInitialisation()
	{
		_frameBufferShader = ResourceManager()->FindAsset<ResourceManagement::ShaderProgram>("- shaders/buffer_shader_shader.glsl");
		_frameBufferVertexArrayObject = std::make_shared<Graphics::VertexArray>();

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

		_frameBufferVertexArrayObject->SetBuffer("Vertex Position Buffer", positionBuffer);
		_frameBufferVertexArrayObject->SetBuffer("Texture UV Buffer", textureUVBuffer);
		_frameBufferVertexArrayObject->SetBuffer("Vertex Normal Buffer", normalBuffer);		
	}

	void Core::Start()
	{
		_running = true;
		MainLoop();
	}

	void Core::MainLoop()
	{
		int i = 0;
		std::chrono::steady_clock::time_point frameStart = std::chrono::steady_clock::now();

		while (_running) [[likely]]
		{
			_inputManager->ProcessFrameInput();

			
			Update();
			

			int physicsCycles = _timeManager->CheckForFixedUpdates();
			for (int i = 0; i < physicsCycles; i++)
			{
				PhysicsUpdate();
				_debugger->LogFixedUpdate();
			}

			Render();

			_timeManager->WaitForEndOfFrame();
			_debugger->LogUpdate();

			if (_inputManager->Input()->QuitEvent())[[unlikely]] _running = false;
		}
	}

	void Core::Render()
	{
		int width = 0, height = 0;
		SDL_GetWindowSize(*_window, &width, &height);

		glViewport(0, 0, width, height);

		GLuint framebufferID = 0, framebufferColourTextureID = 0, frameBufferDepthTextureID = 0;
		SetUpFrameBuffer(framebufferID, framebufferColourTextureID, frameBufferDepthTextureID, width, height);

		/*
		for (int i = 0; i < _cameraList.size(); i++)
		{
			std::shared_ptr<Components::Camera> activeCamera = _cameraList[i].lock();

			activeCamera->GenerateNewProjectionMatrix(width, height, 60.0f);

			for (int j = 0; j < _entityList.size(); j++)
			{
				_entityList[j]->Render(activeCamera->Transform()->TransformationMatrix(), activeCamera->ProjectionMatrix());
			}

			activeCamera->RenderSkybox();
		}
		*/

		ClearFrameBufferAndDrawToMainBuffer(framebufferID, framebufferColourTextureID, frameBufferDepthTextureID);

		SDL_GL_SwapWindow(*_window);
	}

	std::shared_ptr<ResourceManagement::Texture> Core::RenderTexture()
	{
		std::shared_ptr<ResourceManagement::Texture> texture = std::make_shared<ResourceManagement::Texture>();

		int width = 0, height = 0;
		SDL_GetWindowSize(*_window, &width, &height);

		glViewport(0, 0, width, height);

		GLuint framebufferID = 0, framebufferColourTextureID = 0, frameBufferDepthTextureID = 0;
		SetUpFrameBuffer(framebufferID, framebufferColourTextureID, frameBufferDepthTextureID, width, height);


		int channelNumber = 4;
		for (int i = 0; i < _cameraList.size(); i++)
		{
			std::shared_ptr<Components::Camera> activeCamera = _cameraList[i].lock();

			activeCamera->GenerateNewProjectionMatrix(width, height, 60.0f);

			for (int j = 0; j < _entityList.size(); j++)
			{
				_entityList[j]->Render(activeCamera->Transform()->TransformationMatrix(), activeCamera->ProjectionMatrix());
			}

			activeCamera->RenderSkybox();
		}

		int dataLength = width * height * channelNumber;
		GLubyte* textureData = new GLubyte[dataLength];

		glBindTexture(GL_TEXTURE_2D, framebufferColourTextureID);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

		texture->CreateTexture(width, height, channelNumber, textureData);

		glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
		
		glDeleteTextures(1, &framebufferColourTextureID);
		glDeleteRenderbuffers(1, &frameBufferDepthTextureID);
		glDeleteFramebuffers(1, &framebufferID);

		return texture;
	}	

	void Core::SetUpFrameBuffer(GLuint& framebufferID, GLuint& framebufferColourTextureID, GLuint& frameBufferDepthTextureID, int width, int height)
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

	void Core::ClearFrameBufferAndDrawToMainBuffer(GLuint framebufferID, GLuint framebufferColourTextureID, GLuint frameBufferDepthTextureID)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw ErrorHandling::Exception("Failed to create a complete frame buffer.");
		}
		else
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDisable(GL_DEPTH_TEST);

			glUseProgram(_frameBufferShader->GetShaderID());
			glBindVertexArray(_frameBufferVertexArrayObject->GetID());

			glBindTexture(GL_TEXTURE_2D, framebufferColourTextureID);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		glDeleteTextures(1, &framebufferColourTextureID);
		glDeleteRenderbuffers(1, &frameBufferDepthTextureID);
		glDeleteFramebuffers(1, &framebufferID);

		glUseProgram(0);
	}


	void Core::Update()
	{
		for (int i = 0; i < _entityList.size(); i++)
		{
			_entityList[i]->Update();
		}
	}

	void Core::PhysicsUpdate()
	{
		for (int i = 0; i < _entityList.size(); i++)
		{
			_entityList[i]->PhysicsUpdate();
		}
	}

	std::shared_ptr<Entity> Core::AddEntity(std::string name)
	{
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(name);

		entity->Initialise(entity, _self.lock());;
		_entityList.push_back(entity);

		return entity;
	}

	void Core::Stop()
	{
		_running = !_running;
	}

	Core::~Core()
	{
		SDL_DestroyWindow(*_window);
		SDL_Quit();
	}

	std::shared_ptr<Entity> Core::Find(std::string name)
	{
		std::shared_ptr<Entity> foundObject;
		for (int i = 0; i < _entityList.size(); i++)
		{
			if (_entityList[i]->Name().find(name) != std::string::npos)
			{
				foundObject = _entityList[i];
				break;
			}
		}

		return foundObject;
	}

	std::shared_ptr<Core> Core::Self() { return _self.lock(); }
	std::shared_ptr<ResourceManager> Core::ResourceManager() { return _resources; }
	std::shared_ptr<Debugger> Core::Debugger() { return _debugger; }
	std::shared_ptr<TimeManager> Core::TimeManager() { return _timeManager; }
	std::shared_ptr<InputManager> Core::InputManager() { return _inputManager; }
	std::vector<std::weak_ptr<Components::Light>> Core::Lights() { return _lightList; }
}