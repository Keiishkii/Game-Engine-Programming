#pragma once
#ifndef TIME
#define TIME
	#include <chrono>

	namespace Engine
	{
		struct Core;
		struct Time
		{
			friend Engine::Core;

		private:
			float _targetFramerate = 60;
			float _targetDeltaTime;
			float _deltaTime;

			float _physicsUpdateRate = 60;
			float _physicsDeltaTime;

			std::chrono::steady_clock::time_point _timeOfPreviousFrameEnd, _timeOfPreviousPhysicsCheck;
			std::chrono::duration<float> _totalElapsedPhysicsTime;

		private:
			int CheckForFixedUpdates();
			void WaitForEndOfFrame();

			void Sleep(float seconds);

		public:
			Time(float targetFrameRate, float physicsUpdateRate);

			void SetPhysicsUpdateRate(float);
			void SetFrameRate(float);

			float PhysicsDeltaTime() const;
			float DeltaTime() const;
		};
	}
#endif