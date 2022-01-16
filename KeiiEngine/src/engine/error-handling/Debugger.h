#include <chrono>
#include <string>

namespace Engine
{
	struct Core;

	namespace ErrorHandling
	{
		/**	The Debugger is the class used to perform error handling from within the engine and game.  	*/
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