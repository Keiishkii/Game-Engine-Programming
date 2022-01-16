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

		/**	Resource is the base class of all other resources, its purpose is to allow for the ResourceManager to store all resources in a shared dictionary.  	*/
		struct Resource
		{
			friend ResourceManager;

		protected:
			bool _loadBaseClass = false;
			bool _initialisedBaseClass = false;

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