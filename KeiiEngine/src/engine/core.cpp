#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>

#include "Core.h"
#include "Entity.h"
#include "Time.h"
#include "Debugging.h"



std::shared_ptr<Engine::Core> Engine::Core::Initialise()
{
	std::shared_ptr<Engine::Core> core = std::make_shared<Engine::Core>();

	return core;
}

void Engine::Core::Start()
{
	running = true;
	targetUpdatesPerSecond = 60;

	MainLoop();
}

void Engine::Core::MainLoop()
{
	std::shared_ptr<Time> timeClass = std::make_shared<Time>(60, 60);

	std::shared_ptr<Debugging> debug = std::make_shared<Debugging>();

	int i = 0;
	std::chrono::steady_clock::time_point frameStart = std::chrono::steady_clock::now();

	while (running)
	{
		
		Update();
		debug->LogUpdate();

		int physicsCycles = timeClass->CheckForFixedUpdates();
		for (int i = 0; i < physicsCycles; i++)
		{
			PhysicsUpdate();
			debug->LogFixedUpdate();
		}

		timeClass->WaitForEndOfFrame();
	}
}

void Engine::Core::Update()
{
	std::cout << "Update" << std::endl;
	for (int i = 0; i < entityList.size(); i++)
	{
		entityList[i]->Update();
	}
}

void Engine::Core::PhysicsUpdate()
{
	std::cout << "Physics Update" << std::endl;
	for (int i = 0; i < entityList.size(); i++)
	{
		entityList[i]->Update();
	}
}

void Engine::Core::Stop()
{
	running = false;
}

std::shared_ptr<Engine::Entity> Engine::Core::AddEntity()
{
	std::shared_ptr<Engine::Entity> entity = std::make_shared<Engine::Entity>();
	entityList.push_back(entity);

	return entity;
}