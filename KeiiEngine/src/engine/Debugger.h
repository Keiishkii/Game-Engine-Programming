#pragma once

#include <chrono>



namespace Engine
{
	struct Debugger
	{
	private:
		int updates, fixedUpdates;
		std::chrono::steady_clock::time_point lastUpdateTime, lastFixedUpdateTime;
		std::chrono::duration<float> totalUpdateTime, totalFixedUpdateTime;

	public:
		void LogUpdate();
		void LogFixedUpdate();
	};
}