#ifndef RESOURCE_H
#define RESOURCE_H
	#include <string>
	#include <memory>

namespace Engine
{
	struct Core;
	namespace ResourceManagement
	{		
		struct ResourceManager;
		struct Resource
		{
			friend ResourceManager;

		protected:
			std::weak_ptr<ResourceManager> _resourceManager;
			std::weak_ptr<Engine::Core> _core;
		private:
			std::string _name;
		public:


		private:
		public:
			virtual void Initialise(const std::shared_ptr<ResourceManager>& resourceManager);
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath);

			std::shared_ptr<ResourceManagement::ResourceManager> ResourceManager();
			std::shared_ptr<Engine::Core> Core();
			virtual std::string GetName();
		};
	}
}
#endif