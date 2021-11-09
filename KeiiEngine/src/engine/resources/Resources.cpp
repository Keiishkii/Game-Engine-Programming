#include "Resources.h"
#include "Resource.h"
#include "ShaderProgram.h"
#include "engine/error-handling/Exception.h"

#include <Windows.h>
#include <filesystem>
#include <memory>
#include <iostream>
#include <fstream>

namespace Engine
{
	namespace ResourceManagement
	{
		Resources::Resources()
		{
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
		}

		bool Resources::FindResourceFolder()
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