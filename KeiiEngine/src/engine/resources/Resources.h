#pragma once
#ifndef RESOURCES
#define RESOURCES
	#include <memory>
	#include <string>
	#include <fstream>
	#include <map>

namespace Engine
{
	namespace ResourceManagement
	{
		struct Resource;
		struct Resources
		{
		private:
			std::shared_ptr<ResourceManagement::Resources> _resources;

			bool _resourceLocationFound = false;
			std::string _resourceLocation;
			std::map<std::string, std::shared_ptr<Resource>> _loadedAssets;

		public:
			Resources();

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

		private:
			bool FindResourceFolder();
		};
	}
}

#endif