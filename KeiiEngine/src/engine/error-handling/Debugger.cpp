#include <iostream>
#include "Debugger.h"

//#define ENGINE_DEBUGGING
#ifdef ENGINE_DEBUGGING
	//#define ENGINE_DEBUGGING_UPDATE
	//#define ENGINE_DEBUGGING_FIXED-UPDATE
#endif

namespace Engine
{
	namespace ErrorHandling
	{
		void Debugger::Print(std::string content)
		{
			std::cout << "Log: " << content << std::endl;
		}

		void Debugger::PrintWarning(std::string content)
		{
			std::cout << "\x1B[33m" << "Warning: " << "\033[0m" << content << std::endl;
		}

		void Debugger::PrintError(std::string content)
		{
			std::cout << "\x1B[31m" << "Error: " << "\033[0m" << content << std::endl;
		}

		void Debugger::LogUpdate()
		{
			#ifdef ENGINE_DEBUGGING_UPDATE
			{
				std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

				if (updates > 0)
				{
					totalUpdateTime += (currentTime - lastUpdateTime);
					std::cout << "UPDATE: Average FPS: " << ((updates) / totalUpdateTime.count()) << std::endl;
				}

				lastUpdateTime = currentTime;
				updates++;
			}
			#endif
		}

		void Debugger::LogFixedUpdate()
		{
			#ifdef ENGINE_DEBUGGING_FIXED-UPDATE
			{
				std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

				if (fixedUpdates > 0)
				{
					totalFixedUpdateTime += (currentTime - lastFixedUpdateTime);
					std::cout << "FIXED: Average FPS: " << ((fixedUpdates) / totalFixedUpdateTime.count()) << std::endl;
				}

				lastFixedUpdateTime = currentTime;
				fixedUpdates++;
			}
			#endif
		}
	}
}