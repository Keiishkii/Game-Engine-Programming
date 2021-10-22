#include <thread>
#include <cmath>
#include <iostream>
#include <Windows.h>

#include "Time.h"



float Engine::Time::PhysicsDeltaTime() const { return _physicsDeltaTime; }
float Engine::Time::DeltaTime() const { return _deltaTime; }

void Engine::Time::SetPhysicsUpdateRate(float updateRate)
{
	updateRate = fmaxf(1.0f, updateRate);

	_physicsUpdateRate = updateRate;
	_physicsDeltaTime = 1.0f / updateRate;
}

void Engine::Time::SetFrameRate(float frameRate)
{
	frameRate = fmaxf(1.0f, frameRate);

	_targetFramerate = frameRate;
	_targetDeltaTime = 1.0f / frameRate;
}





Engine::Time::Time(float targetFrameRate, float physicsUpdateRate)
{
	SetFrameRate(targetFrameRate);
	SetPhysicsUpdateRate(physicsUpdateRate);

	_timeOfPreviousFrameEnd = std::chrono::steady_clock::now();
	_timeOfPreviousPhysicsCheck = std::chrono::steady_clock::now();
	_totalElapsedPhysicsTime = std::chrono::duration<float>(0);
}





int Engine::Time::CheckForFixedUpdates()
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> timeElapsed = currentTime - _timeOfPreviousPhysicsCheck;

	_totalElapsedPhysicsTime += timeElapsed;
		
	int fixedUpdateCycles = (_totalElapsedPhysicsTime.count() / _physicsDeltaTime);

	_totalElapsedPhysicsTime -= std::chrono::duration<float>((float) fixedUpdateCycles * _physicsDeltaTime);
	_timeOfPreviousPhysicsCheck = currentTime;

	return fixedUpdateCycles;
}

void Engine::Time::WaitForEndOfFrame()
{
	std::chrono::duration<float> timeElapsed = std::chrono::steady_clock::now() - _timeOfPreviousFrameEnd;
	float waitDuration = (1 / _targetFramerate) - timeElapsed.count();

	if (waitDuration > 0)
	{
		Sleep(waitDuration);
		//::_sleep(waitDuration);
		//::Sleep((int)(waitDuration * 1000.0f));
		//std::this_thread::sleep_for(std::chrono::milliseconds((int) (waitDuration * 1000.0f)));
		//std::this_thread::sleep_for(std::chrono::milliseconds((int) (1)));
		//std::this_thread::sleep_for(std::chrono::milliseconds((int) (0)));
	}

	std::chrono::steady_clock::time_point timeAfterSleep = std::chrono::steady_clock::now();

	timeElapsed = timeAfterSleep - _timeOfPreviousFrameEnd;
	_deltaTime = timeElapsed.count();

	//std::cout << "FPS: " << (1 / _deltaTime) << std::endl;

	_timeOfPreviousFrameEnd = timeAfterSleep;
}





void Engine::Time::Sleep(float seconds)
{
	std::chrono::duration<float> waitDuration = std::chrono::duration<float>(seconds);
	
	std::chrono::steady_clock::time_point sleepFunctionStart = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsedTime = std::chrono::steady_clock::now() - sleepFunctionStart;
	while (elapsedTime < waitDuration)
	{
		elapsedTime = std::chrono::steady_clock::now() - sleepFunctionStart;
	}
}