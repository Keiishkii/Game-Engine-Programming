#include <memory>
#include <string>
#include <fstream>
#include <map>
#include <fbxsdk.h>

namespace Engine
{
	struct Core;

	namespace ResourceManagement
	{
		struct Resource;
		struct ResourceManager
		{
		private:
			std::weak_ptr<Core> _core;
			std::weak_ptr<ResourceManager> _self;

			std::shared_ptr<FbxManager*> _fbxManager;

			bool _resourceLocationFound = false;
			std::string _resourceLocation;
			std::map<std::string, std::shared_ptr<Resource>> _loadedAssets;		
		public:


		private:
			bool FindResourceFolder();
			void FBXInitialisation();
		public:
			void Initialise(std::weak_ptr<ResourceManager> self, std::weak_ptr<Core> corePtr);

			template <typename T>
			std::shared_ptr<T> FindAsset(std::string assetPath)
			{
				std::shared_ptr<T> resourcePointer = std::make_shared<T>();

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
		};
	}
}