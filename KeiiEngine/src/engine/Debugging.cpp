#include "Debugging.h"
#include <iostream>

void Engine::Debugging::LogUpdate()
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	if (updates > 0)
	{
		totalUpdateTime += (currentTime - lastUpdateTime);
		std::cout << "Average FPS: " << ((updates) / totalUpdateTime.count());
	}

	lastUpdateTime = currentTime;
	updates++;
}

void Engine::Debugging::LogFixedUpdate()
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	if (fixedUpdates > 0)
	{
		totalFixedUpdateTime += (currentTime - lastFixedUpdateTime);
		std::cout << "Average FPS: " << ((fixedUpdates) / totalFixedUpdateTime.count());
	}

	lastFixedUpdateTime = currentTime;
	fixedUpdates++;
}