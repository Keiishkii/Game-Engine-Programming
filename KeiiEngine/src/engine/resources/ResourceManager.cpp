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
		ResourceManager::~ResourceManager()
		{
			(*_fbxManager)->Destroy();
		}

		std::shared_ptr<FbxManager*> ResourceManager::FBXManager() { return _fbxManager; }

		void ResourceManager::Initialise(std::weak_ptr<ResourceManager> self, std::weak_ptr<Engine::Core> corePtr)
		{
			std::shared_ptr<ResourceManager> resourceManager = self.lock();

			resourceManager->_self = self;
			resourceManager->_core = corePtr;

			try
			{
				if (!FindResourceFolder())
				{
					throw ErrorHandling::Exception("Could not find the 'Resource' folder location.");
				}
			}
			catch (ErrorHandling::Exception e)
			{
				e.Print();
			}

			FBXInitialisation();
		}

		void ResourceManager::FBXInitialisation()
		{
			_fbxManager = std::make_shared<FbxManager*>(FbxManager::Create());

			try
			{
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
			catch (ErrorHandling::Exception e)
			{
				e.Print();
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
	}
}