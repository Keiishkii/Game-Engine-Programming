#include <chrono>

namespace Engine
{
	namespace ErrorHandling
	{
		struct Debugger
		{
		private:
			int updates, fixedUpdates;
			std::chrono::steady_clock::time_point lastUpdateTime, lastFixedUpdateTime;
			std::chrono::duration<float> totalUpdateTime, totalFixedUpdateTime;
		public:


		private:
		public:
			void LogUpdate();
			void LogFixedUpdate();
		};
	}
}