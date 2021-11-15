#include "Resource.h"

namespace Engine
{
	namespace ResourceManagement
	{
		void Resource::Initialise(std::weak_ptr<ResourceManager> resourceManager)
		{
			_resourceManager = resourceManager;
		}

		void Resource::Load(std::string path)
		{

		}
	}
}