#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"


#include "ResourceManager.h"
#include "Resource.h"
#include "ShaderProgram.h"
#include "engine/error-handling/Exception.h"
#include "engine/Core.h"

#include <Windows.h>
#include <filesystem>
#include <memory>
#include <iostream>
#include <fstream>
#include <fbxsdk.h>

using Engine::ErrorHandling::Exception;
using rapidjson::Document;

namespace Engine
{
	namespace ResourceManagement
	{
		#pragma region Static Functions

		bool ResourceManager::FileExists(std::string path)
		{
			std::fstream fileStream;
			fileStream.open(path);

			bool fileExists = fileStream.is_open();
			fileStream.close();

			return fileExists;
		}

		std::string ResourceManager::ReadText(std::string path)
		{
			std::string fileContent = "";

			std::fstream fileStream;
			fileStream.open(path);

			if (fileStream.is_open())
			{
				std::string fileLine = "";
				while (std::getline(fileStream, fileLine))
				{
					fileContent += fileLine + "\n";
				}
			}

			return fileContent;
		}

		Document ResourceManager::ToJSON(std::string jsonString)
		{
			Document document;
			document.Parse(jsonString.c_str());

			return document;
		}

		#pragma endregion



		void ResourceManager::Initialise(const std::shared_ptr<ResourceManager>& self, const std::shared_ptr<Engine::Core>& core)
		{
			self->_self = self;
			self->_core = core;
			
			if (!(_resourceLocationFound || FindResourceFolder()))
			{
				throw Exception("Could not find the 'Resource' folder location.");
			}
			else
			{
				FBXInitialisation();
			}
		}

		void ResourceManager::FBXInitialisation()
		{
			_fbxManager = std::make_shared<FbxManager*>(FbxManager::Create());

			if (!_fbxManager)
			{
				throw Exception("Failed to set relative mouse position");
			}
			else
			{
				FbxIOSettings* ios = FbxIOSettings::Create(*_fbxManager, IOSROOT);
				(*_fbxManager)->SetIOSettings(ios);

				FbxString lPath = FbxGetApplicationDirectory();
				(*_fbxManager)->LoadPluginsDirectory(lPath.Buffer());
			}
		}

		bool ResourceManager::FindResourceFolder()
		{
			char executablePathAsArray[_MAX_PATH];
			GetModuleFileName(NULL, executablePathAsArray, _MAX_PATH - 1);

			std::string executablePath = executablePathAsArray;
			std::string fileName = executablePath.substr(executablePath.find_last_of("/\\"));
			fileName = fileName.substr(0, fileName.size() - 4);

			std::string resourceDirectory = executablePath;

			int positionOfParentDirectory = resourceDirectory.find_last_of("/\\");
			while (positionOfParentDirectory > 0 && !_resourceLocationFound)
			{
				resourceDirectory = resourceDirectory.substr(0, positionOfParentDirectory);

				DWORD dwAttrib = GetFileAttributes((resourceDirectory + fileName).c_str());
				if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
				{
					_resourceLocationFound = true;
					_resourceLocation = resourceDirectory + fileName + "\//";
				}

				positionOfParentDirectory = resourceDirectory.find_last_of("/\\");
			}

			return _resourceLocationFound;
		}

		ResourceManager::~ResourceManager()
		{
			(*_fbxManager)->Destroy();
		}

		std::string ResourceManager::GetResourceDirectory()
		{
			std::string directory;
			if (_resourceLocationFound || FindResourceFolder())
			{
				directory = _resourceLocation;
			}

			return directory;
		}

		std::shared_ptr<FbxManager*>& ResourceManager::FBXManager() { return _fbxManager; }
		std::shared_ptr<ResourceManager> ResourceManager::Self() { return _self.lock(); }
		std::shared_ptr<Engine::Core> ResourceManager::Core() { return _core.lock(); }
	}
}