#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <glew.h>

#include "Core.h"
#include "Time.h"
#include "Entity.h"
#include "components/Camera.h"
#include "error-handling/Debugger.h"
#include "error-handling/Exception.h"
#include "resources/ResourceManager.h"

	using Engine::ErrorHandling::Exception;
	using Engine::ErrorHandling::Debugger;
	using Engine::ResourceManagement::ResourceManager;

namespace Engine
{
	std::shared_ptr<ResourceManager> Core::ResourceManager() { return _resources; }
	std::shared_ptr<Debugger> Core::Debugger() { return _debugger; }

	std::shared_ptr<Core> Core::Initialise()
	{
		std::shared_ptr<Core> core = std::make_shared<Core>();

		core->_self = core;
		core->_debugger = std::make_shared<ErrorHandling::Debugger>();
		core->_resources = std::make_shared<ResourceManagement::ResourceManager>();
		core->_resources->Initialise(core->_resources, core);

		core->SDLInitialisation();

		return core;
	}

	void Core::SDLInitialisation()
	{
		_window = std::make_shared<SDL_Window*>(SDL_CreateWindow("Keii Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));

		try
		{
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
				}
			}
		}
		catch (Exception e)
		{
			e.Print();
		}
	}

	Core::~Core()
	{
		SDL_DestroyWindow(*_window);
		SDL_Quit();
	}

	void Core::Start()
	{
		_running = true;

		MainLoop();
	}

	void Core::MainLoop()
	{
		std::shared_ptr<Time> timeClass = std::make_shared<Time>(80, 120);

		int i = 0;
		std::chrono::steady_clock::time_point frameStart = std::chrono::steady_clock::now();

		while (_running)
		{
			Update();

			int physicsCycles = timeClass->CheckForFixedUpdates();
			for (int i = 0; i < physicsCycles; i++)
			{
				PhysicsUpdate();
				_debugger->LogFixedUpdate();
			}

			Render();
			timeClass->WaitForEndOfFrame();

			_debugger->LogUpdate();
		}
	}

	void Core::Render()
	{
		glClearColor(0.125f, 0.4f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		std::cout << " - Render" << std::endl;
		for (int i = 0; i < _cameraList.size(); i++)
		{
			_activeCamera = _cameraList[i];
			for (int i = 0; i < _entityList.size(); i++)
			{
				_entityList[i]->Render();
			}
		}

		glUseProgram(0);
		SDL_GL_SwapWindow(*_window);
	}

	void Core::Update()
	{
		std::cout << " - Update" << std::endl;
		for (int i = 0; i < _entityList.size(); i++)
		{
			_entityList[i]->Update();
		}
	}

	void Core::PhysicsUpdate()
	{
		std::cout << " - Physics Update" << std::endl;
		for (int i = 0; i < _entityList.size(); i++)
		{
			_entityList[i]->Update();
		}
	}

	void Core::Stop()
	{
		_running = false;
	}

	std::shared_ptr<Entity> Core::AddEntity()
	{
		std::shared_ptr<Entity> entity = Entity::Initialise(_self);;
		_entityList.push_back(entity);

		return entity;
	}
}