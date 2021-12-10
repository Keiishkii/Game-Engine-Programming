#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <glew.h>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Inputs.h"
#include "Entity.h"
#include "Scene.h"
#include "components/Camera.h"
#include "components/Transform.h"
#include "error-handling/Debugger.h"
#include "error-handling/Exception.h"
#include "graphics/GraphicsManager.h"
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
		core->_resourceManager = std::make_shared<ResourceManagement::ResourceManager>();
		core->_resourceManager->Initialise(core->_resourceManager, core);
		core->_graphicsManager = std::make_shared<Graphics::GraphicsManager>();
		core->_graphicsManager->Initialise(core);

		core->_timeManager = std::make_shared<Engine::TimeManager>(FPS, fixedFPS);
		core->_inputManager = std::make_shared<Engine::InputManager>();

		core->SDLInitialisation();

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

			if (_inputManager->Input()->QuitEvent()) [[unlikely]] _running = false;
		}
	}

	void Core::Render()
	{
		int width = 0, height = 0;
		SDL_GetWindowSize(*_window, &width, &height);

		glViewport(0, 0, width, height);


		// - - Render the scene to a GLTexture
		GLuint renderTexture = 0;

		std::shared_ptr<Components::Camera> mainCamera = ActiveScene()->MainCamera();
		if (mainCamera)
		{
			mainCamera->GenerateNewProjectionMatrix(width, height, 45);
			renderTexture = ActiveScene()->RenderSceneToTextureBuffer(mainCamera->Transform()->TransformationMatrix(), mainCamera->ProjectionMatrix(), width, height);
		

			// - - Draw GLTexture to the screen Quad
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDisable(GL_DEPTH_TEST);

			glUseProgram(GraphicsManager()->GetPostProcessingShader()->GetShaderID());
			glBindVertexArray(GraphicsManager()->Quad()->GetID());

			glBindTexture(GL_TEXTURE_2D, renderTexture);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDeleteTextures(1, &renderTexture);
		}

		SDL_GL_SwapWindow(*_window);
	}

	void Core::Update()
	{
		_activeScene->Update();
	}

	void Core::PhysicsUpdate()
	{
		_activeScene->PhysicsUpdate();
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

	std::shared_ptr<Core> Core::Self() { return _self.lock(); }
	std::shared_ptr<Scene> Core::ActiveScene() { return _activeScene; }

	std::shared_ptr<Debugger> Core::Debugger() { return _debugger; }

	std::shared_ptr<Graphics::GraphicsManager> Core::GraphicsManager() { return _graphicsManager; }
	std::shared_ptr<ResourceManager> Core::ResourceManager() { return _resourceManager; }
	std::shared_ptr<TimeManager> Core::TimeManager() { return _timeManager; }
	std::shared_ptr<InputManager> Core::InputManager() { return _inputManager; }
}