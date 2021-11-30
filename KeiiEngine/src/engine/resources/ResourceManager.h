#include <memory>
#include <string>
#include <fstream>
#include <map>
#include <fbxsdk.h>

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

			std::weak_ptr<Core> _core;
			std::weak_ptr<ResourceManager> _self;

			std::map<std::string, std::shared_ptr<Resource>> _loadedAssets;		
		public:


		private:
			bool FindResourceFolder();
			void FBXInitialisation();

			std::shared_ptr<ResourceManager> Self();
		public:
			void Initialise(const std::shared_ptr<ResourceManager>& self, const std::shared_ptr<Engine::Core>& core);
			~ResourceManager();

			template <typename T>
			std::shared_ptr<T> FindAsset(std::string assetPath)
			{
				std::shared_ptr<T> resourcePointer = std::make_shared<T>();
				std::shared_ptr<ResourceManager> self = Self();

				resourcePointer->Resource::Initialise(self);
				resourcePointer->Initialise(self);

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
							std::string completeAssetPath = _resourceLocation + assetPath;

							std::fstream fileStream;
							fileStream.open(completeAssetPath);
							if (fileStream.is_open())
							{
								fileStream.close();

								std::string fileType = assetPath.substr(assetPath.find_last_of("."));

								resourcePointer->Load(completeAssetPath);

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
			std::string GetResourceDirectory();
		};
	}
}