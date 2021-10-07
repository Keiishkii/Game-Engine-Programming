#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include "Core.h"
#include "Entity.h"



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
	int i = 0;
	std::chrono::steady_clock::time_point frameStart = std::chrono::high_resolution_clock::now();

	while (running)
	{
		std::chrono::steady_clock::time_point frameEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - frameStart;
		
		int waitDuration = (int)(1000.f * std::fmaxf(elapsed.count() - (1 / (float)targetUpdatesPerSecond), 0));

		std::this_thread::sleep_for(std::chrono::milliseconds(waitDuration));

		std::cout << "Elaped: " << elapsed.count() << std::endl;
		frameStart = std::chrono::high_resolution_clock::now();


		// Create Time Class -> Let the time class calculate above code and halt loop.
		// Create Enviroment Class -> Let enviroment perform ticks on things
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