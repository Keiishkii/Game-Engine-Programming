#include <chrono>

namespace Engine
{
	struct Core;
	struct TimeManager
	{
		friend Engine::Core;

	private:
		float _targetFramerate = 60;
		float _targetDeltaTime;
		float _deltaTime;

		float _physicsUpdateRate = 60;
		float _physicsDeltaTime;

		std::chrono::steady_clock::time_point _timeOfProgramStart, _timeOfPreviousFrameEnd, _timeOfPreviousPhysicsCheck;
		std::chrono::duration<float> _totalElapsedPhysicsTime;

	private:
		int CheckForFixedUpdates();
		void WaitForEndOfFrame();

		void Sleep(float seconds);

	public:
		TimeManager(float targetFrameRate, float physicsUpdateRate);

		float TimeSinceStartOfProgram();

		void SetPhysicsUpdateRate(float);
		void SetFrameRate(float);

		float PhysicsDeltaTime() const;
		float DeltaTime() const;
	};
}