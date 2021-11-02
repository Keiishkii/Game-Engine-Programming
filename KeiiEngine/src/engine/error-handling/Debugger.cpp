#include <iostream>
#include "Debugger.h"

void Engine::ErrorHandling::Debugger::LogUpdate()
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	if (updates > 0)
	{
		totalUpdateTime += (currentTime - lastUpdateTime);
		std::cout << "UPDATE: Average FPS: " << ((updates) / totalUpdateTime.count()) << std::endl;
	}

	lastUpdateTime = currentTime;
	updates++;
}

void Engine::ErrorHandling::Debugger::LogFixedUpdate()
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	if (fixedUpdates > 0)
	{
		totalFixedUpdateTime += (currentTime - lastFixedUpdateTime);
		std::cout << "FIXED: Average FPS: " << ((fixedUpdates) / totalFixedUpdateTime.count()) << std::endl;
	}

	lastFixedUpdateTime = currentTime;
	fixedUpdates++;
}