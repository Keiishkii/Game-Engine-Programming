#include <chrono>

namespace Engine
{
	struct Core;

	namespace ErrorHandling
	{
		struct Debugger
		{
			friend Core;

		private:
			int updates, fixedUpdates;
			std::chrono::steady_clock::time_point lastUpdateTime, lastFixedUpdateTime;
			std::chrono::duration<float> totalUpdateTime, totalFixedUpdateTime;
		public:


		private:
			void LogUpdate();
			void LogFixedUpdate();
		public:
			static void Print(std::string content);
			static void PrintWarning(std::string content);
			static void PrintError(std::string content);
		};
	}
}