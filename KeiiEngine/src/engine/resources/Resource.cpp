#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void Resource::Initialise(const std::shared_ptr<ResourceManager>& resourceManager)
		{
			_resourceManager = resourceManager;
		}

		void Resource::Load(const std::string& path) { }
	}
}