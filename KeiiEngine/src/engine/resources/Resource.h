#ifndef RESOURCE_H
#define RESOURCE_H
	#include <string>
	#include <memory>

namespace Engine
{
	namespace ResourceManagement
	{		
		struct ResourceManager;

		struct Resource
		{
			friend ResourceManager;

		protected:
			std::weak_ptr<ResourceManager> _resourceManager;
		private:
		public:


		private:
		public:
			virtual void Initialise(const std::shared_ptr<ResourceManager>& resourceManager);
			virtual void Load(const std::string& path);
		};
	}
}
#endif