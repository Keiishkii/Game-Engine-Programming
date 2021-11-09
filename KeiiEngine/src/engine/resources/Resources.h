#pragma once
#ifndef RESOURCES
#define RESOURCES
	#include <memory>
	#include <string>
	#include <map>

namespace Engine
{
	namespace ResourceManagement
	{
		struct Resource;
		struct Resources
		{
		private:
			enum SupportedFileTypes {UNSUPPORTED, TXT, FBX, MP3, PNG, SHADER};
			const static std::map<std::string, SupportedFileTypes> _stringToFileType;

			bool _resourceLocationFound = false;
			std::string _resourceLocation;
			std::map<std::string, std::shared_ptr<Resource>> _loadedAssets;

		public:
			std::shared_ptr<Resource> FindAsset(std::string assetPath);

		private:
			bool FindResourceFolder();
		};
	}
}

#endif