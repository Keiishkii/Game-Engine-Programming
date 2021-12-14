#include <thread>
#include <cmath>
#include <iostream>
#include <Windows.h>

#include "TimeManager.h"


namespace Engine
{
	Engine::TimeManager::TimeManager(float targetFrameRate, float physicsUpdateRate)
	{
		SetFrameRate(targetFrameRate);
		SetPhysicsUpdateRate(physicsUpdateRate);

		_timeOfProgramStart = std::chrono::steady_clock::now();
		_timeOfPreviousFrameEnd = std::chrono::steady_clock::now();
		_timeOfPreviousPhysicsCheck = std::chrono::steady_clock::now();
		_totalElapsedPhysicsTime = std::chrono::duration<float>(0);
	}

	float TimeManager::TimeSinceStartOfProgram()
	{
		std::chrono::duration<float> duration = std::chrono::steady_clock::now() - _timeOfProgramStart;
		return duration.count();
	}

	void Engine::TimeManager::SetPhysicsUpdateRate(float updateRate)
	{
		updateRate = fmaxf(1.0f, updateRate);

		_physicsUpdateRate = updateRate;
		_physicsDeltaTime = 1.0f / updateRate;
	}

	void Engine::TimeManager::SetFrameRate(float frameRate)
	{
		frameRate = fmaxf(1.0f, frameRate);

		_targetFramerate = frameRate;
		_targetDeltaTime = 1.0f / frameRate;
	}

	int Engine::TimeManager::CheckForFixedUpdates()
	{
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> timeElapsed = currentTime - _timeOfPreviousPhysicsCheck;

		_totalElapsedPhysicsTime += timeElapsed;

		int fixedUpdateCycles = (_totalElapsedPhysicsTime.count() / _physicsDeltaTime);
		if (!fixedUpdateCycles > _maxPhysicsFrames) [[unlikely]]
			fixedUpdateCycles = _maxPhysicsFrames;

		_totalElapsedPhysicsTime -= std::chrono::duration<float>((float)fixedUpdateCycles * _physicsDeltaTime);
		_timeOfPreviousPhysicsCheck = currentTime;

		return fixedUpdateCycles;
	}

	void Engine::TimeManager::WaitForEndOfFrame()
	{
		std::chrono::duration<float> timeElapsed = std::chrono::steady_clock::now() - _timeOfPreviousFrameEnd;
		float waitDuration = (1 / _targetFramerate) - timeElapsed.count();

		if (waitDuration > 0)
		{
			//Sleep(waitDuration);
			//::_sleep(waitDuration);
			//::Sleep((int)(waitDuration * 1000.0f));
			//std::this_thread::sleep_for(std::chrono::milliseconds((int) (waitDuration * 1000.0f)));
			//std::this_thread::sleep_for(std::chrono::milliseconds((int) (1)));
			//std::this_thread::sleep_for(std::chrono::milliseconds((int) (0)));
		}

		std::chrono::steady_clock::time_point timeAfterSleep = std::chrono::steady_clock::now();

		timeElapsed = timeAfterSleep - _timeOfPreviousFrameEnd;
		_deltaTime = timeElapsed.count();

		_timeOfPreviousFrameEnd = timeAfterSleep;
	}

	void Engine::TimeManager::Sleep(float seconds)
	{
		std::chrono::duration<float> waitDuration = std::chrono::duration<float>(seconds);

		std::chrono::steady_clock::time_point sleepFunctionStart = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsedTime = std::chrono::steady_clock::now() - sleepFunctionStart;
		
		while (elapsedTime < waitDuration)
		{
			elapsedTime = std::chrono::steady_clock::now() - sleepFunctionStart;
		}
	}

	float Engine::TimeManager::PhysicsDeltaTime() const { return _physicsDeltaTime; }
	float Engine::TimeManager::DeltaTime() const { return _deltaTime; }
}