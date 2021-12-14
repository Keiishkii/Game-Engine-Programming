#include <memory>
#include <string>
#include <map>
#include <fbxsdk.h>
#include "rapidjson/document.h"

namespace Engine
{
	struct Core;

	namespace ErrorHandling	{ struct Exception; }
	namespace ResourceManagement
	{
		struct Resource;
		struct ResourceManager
		{
		private:
			bool _resourceLocationFound = false;
			std::string _resourceLocation;

			std::shared_ptr<FbxManager*> _fbxManager;

			std::weak_ptr<Engine::Core> _core;
			std::weak_ptr<ResourceManager> _self;

			std::map<std::string, std::shared_ptr<Resource>> _loadedAssets;		
		public:


		private:
			bool FindResourceFolder();
			void FBXInitialisation();

			std::shared_ptr<ResourceManager> Self();
		public:
			static bool FileExists(std::string path);
			static std::string ReadText(std::string path);
			static rapidjson::Document ToJSON(std::string content);

			void Initialise(const std::shared_ptr<ResourceManager>& self, const std::shared_ptr<Engine::Core>& core);
			~ResourceManager();

			template <typename T>
			std::shared_ptr<T> Create()
			{
				std::shared_ptr<T> resourcePointer = std::make_shared<T>();
				std::shared_ptr<ResourceManager> self = Self();

				resourcePointer->Resource::Initialise(self);
				resourcePointer->Initialise(self);

				return resourcePointer;
			}

			template <typename T>
			std::shared_ptr<T> FindAsset(std::string assetPath)
			{
				std::shared_ptr<T> resourcePointer = Create<T>();

				try
				{
					if (_loadedAssets.count(assetPath))
					{
						resourcePointer = std::dynamic_pointer_cast<T>(_loadedAssets[assetPath]);
						if (!resourcePointer)
						{
							throw ErrorHandling::Exception("Dynamic cast failed.");
						}
					}
					else
					{
						if (_resourceLocationFound)
						{
							if (FileExists(_resourceLocation + assetPath))
							{
								resourcePointer->Resource::Load(_resourceLocation, assetPath);
								resourcePointer->Load(_resourceLocation, assetPath);

								_loadedAssets.insert(std::pair<std::string, std::shared_ptr<Resource>>(assetPath, resourcePointer));
							}
							else
							{
								throw ErrorHandling::Exception("Failed to load asset \"" + assetPath + "\".");
							}
						}
						else
						{
							throw ErrorHandling::Exception("'Resource' folder not set.");
						}
					}
				}
				catch (ErrorHandling::Exception e)
				{
					e.Print();
				}

				return resourcePointer;
			}

			std::shared_ptr<FbxManager*>& FBXManager();
			std::shared_ptr<Engine::Core> Core();
			std::string GetResourceDirectory();
		};
	}
}