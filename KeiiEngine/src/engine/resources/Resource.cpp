#include "Resource.h"
#include "engine/Core.h"
#include "ResourceManager.h"
#include "engine/error-handling/Debugger.h"


using Engine::ErrorHandling::Debugger;

namespace Engine
{
	namespace ResourceManagement
	{
		void Resource::Initialise(const std::shared_ptr<ResourceManagement::ResourceManager>& resourceManager)
		{
			if (!_initialisedBaseClass)
			{
				_resourceManager = resourceManager;
				_core = resourceManager->Core();

				_initialisedBaseClass = true;
			}
		}

		void Resource::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			if (!_loadBaseClass)
			{
				_name = subPath;
			
				#ifdef DEBUG
				{
					Debugger::Print("\x1B[36m" + std::string("Resource") + "\033[0m" + " loaded - (\"" + subPath + "\")");
				}
				#endif // DEBUG

				_loadBaseClass = true;
			}
		}

		std::string Resource::GetName() { return _name; }
		std::shared_ptr<Engine::Core> Resource::Core() { return _core.lock(); }
		std::shared_ptr<ResourceManagement::ResourceManager> Resource::ResourceManager() { return _resourceManager.lock(); }
	}
}