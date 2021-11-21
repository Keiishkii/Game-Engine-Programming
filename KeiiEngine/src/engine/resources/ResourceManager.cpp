#define STB_IMAGE_IMPLEMENTATION
#include "glm/stb_image.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "ShaderProgram.h"
#include "engine/error-handling/Exception.h"
#include "engine/core.h"

#include <Windows.h>
#include <filesystem>
#include <memory>
#include <iostream>
#include <fstream>
#include <fbxsdk.h>

using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace ResourceManagement
	{
		void ResourceManager::Initialise(const std::shared_ptr<ResourceManager>& self, const std::shared_ptr<Engine::Core>& core)
		{
			self->_self = self;
			self->_core = core;

			try
			{
				if (!FindResourceFolder())
				{
					throw Exception("Could not find the 'Resource' folder location.");
				}
				else
				{
					FBXInitialisation();
				}
			}
			catch (Exception e)
			{
				e.Print();
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
				//std::cout << "The path fo the file is: \n - " << resourceDirectory << ". With pos: " << positionOfParentDirectory << std::endl;

				DWORD dwAttrib = GetFileAttributes((resourceDirectory + fileName).c_str());
				//std::cout << "Searching for directory: \n - " << resourceDirectory + fileName << std::endl;
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

		std::shared_ptr<FbxManager*>& ResourceManager::FBXManager() { return _fbxManager; }
		std::shared_ptr<ResourceManager> ResourceManager::Self() { return _self.lock(); }
	}
}