#include "Resources.h"
#include "Resource.h"

#include <Windows.h>
#include <iostream>

namespace Engine
{
	namespace ResourceManagement
	{
		std::shared_ptr<Resource> Engine::ResourceManagement::Resources::FindAsset(std::string assetPath)
		{
			bool assetFound = false;
			if (_loadedAssets[assetPath] != _loadedAssets.end)
			{
				assetFound = true;
			}
			else
			{
				char executablePathAsArray[_MAX_PATH];
				GetModuleFileName(NULL, executablePathAsArray, _MAX_PATH - 1);

				std::string executablePath = executablePathAsArray;
				std::cout << "The path fo the file is: " << executablePath << std::endl;

				//_resourceLocation = 
			}
		}
	}
}