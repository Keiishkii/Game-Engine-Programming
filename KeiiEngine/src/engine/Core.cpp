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
#include "resources/ResourceManager.h"

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

		return core;
	}

	void Core::SDLInitialisation()
	{
		_window = std::make_shared<SDL_Window*>(SDL_CreateWindow("Keii Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 2000, 1200, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));

		try
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

			if (!SDL_GL_CreateContext(*_window))
			{
				throw Exception("Failed to create window context");
			}
			else
			{
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
					else
					{
						std::cout << "Successfuly initialised graphics libuaries" << std::endl;
					}
				}
			}
		}
		catch (Exception e)
		{
			e.Print();
		}
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

			if (_running)[[likely]] _running = !(_inputManager->Input()->QuitEvent());
		}
	}

	void Core::Render()
	{
		int width = 0, height = 0;
		SDL_GetWindowSize(*_window, &width, &height);

		glViewport(0, 0, width, height);

		for (int i = 0; i < _cameraList.size(); i++)
		{
			std::shared_ptr<Components::Camera> activeCamera = _cameraList[i].lock();

			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);

			activeCamera->GenerateNewProjectionMatrix(width, height, 60.0f);

			for (int j = 0; j < _entityList.size(); j++)
			{
				_entityList[j]->Render(activeCamera);
			}

			activeCamera->RenderSkybox();
		}

		glUseProgram(0);
		SDL_GL_SwapWindow(*_window);
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
			_entityList[i]->Update();
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
}