#include <chrono>

namespace Engine
{
	struct Core;

	/**	The TimeManager class is used to keep time flow correct during the program.  	*/
	struct TimeManager
	{
		friend Engine::Core;

	private:
		float _targetFramerate = 60;
		float _targetDeltaTime = 1;
		float _deltaTime = 1;

		int _maxPhysicsFrames = 10;
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