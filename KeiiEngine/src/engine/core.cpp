#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <SDL.h>

#include "Core.h"
#include "Entity.h"
#include "Time.h"
#include "Debugger.h"

#define WINDOW_WIDTH 800	
#define WINDOW_HEIGHT 600

std::shared_ptr<Engine::Core> Engine::Core::Initialise()
{
	std::shared_ptr<Engine::Core> core = std::make_shared<Engine::Core>();

	core->_window = std::make_shared<SDL_Window*>(SDL_CreateWindow("Graphics Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
	core->_debugger = std::make_shared<Debugger>();

	return core;
}

Engine::Core::~Core()
{
	SDL_DestroyWindow(*_window);
}

void Engine::Core::Start()
{
	running = true;
	targetUpdatesPerSecond = 60;

	MainLoop();
}

void Engine::Core::MainLoop()
{
	std::shared_ptr<Time> timeClass = std::make_shared<Time>(80, 120);

	int i = 0;
	std::chrono::steady_clock::time_point frameStart = std::chrono::steady_clock::now();

	while (running)
	{
		
		Update();
		_debugger->LogUpdate();

		int physicsCycles = timeClass->CheckForFixedUpdates();
		for (int i = 0; i < physicsCycles; i++)
		{
			PhysicsUpdate();
			_debugger->LogFixedUpdate();
		}

		timeClass->WaitForEndOfFrame();
	}
}

void Engine::Core::Update()
{
	std::cout << " - Update" << std::endl;
	for (int i = 0; i < _entityList.size(); i++)
	{
		_entityList[i]->Update();
	}
}

void Engine::Core::PhysicsUpdate()
{
	std::cout << " - Physics Update" << std::endl;
	for (int i = 0; i < _entityList.size(); i++)
	{
		_entityList[i]->Update();
	}
}

void Engine::Core::Stop()
{
	running = false;
}

std::shared_ptr<Engine::Entity> Engine::Core::AddEntity()
{
	std::shared_ptr<Engine::Entity> entity = Entity::Initialise(_self);;
	_entityList.push_back(entity);

	

	return entity;
}