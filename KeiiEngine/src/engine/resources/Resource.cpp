#include "Resource.h"
#include "engine/Core.h"
#include "ResourceManager.h"


namespace Engine
{
	namespace ResourceManagement
	{
		void Resource::Initialise(const std::shared_ptr<ResourceManagement::ResourceManager>& resourceManager)
		{
			_resourceManager = resourceManager;
			_core = resourceManager->Core();
		}

		void Resource::Load(const std::string& resourcesDirectory, const std::string& subPath) { }

		std::shared_ptr<Engine::Core> Resource::Core() { return _core.lock(); }
		std::shared_ptr<ResourceManagement::ResourceManager> Resource::ResourceManager() { return _resourceManager.lock(); }
	}
}