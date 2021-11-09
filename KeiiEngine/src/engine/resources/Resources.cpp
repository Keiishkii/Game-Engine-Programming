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
		const std::map<std::string, Engine::ResourceManagement::Resources::SupportedFileTypes> Engine::ResourceManagement::Resources::_stringToFileType		{
			{".txt", SupportedFileTypes::TXT},
			{".fbx", SupportedFileTypes::FBX},
			{".mp3", SupportedFileTypes::MP3},
			{".png", SupportedFileTypes::PNG},
			{".shader", SupportedFileTypes::SHADER}
		};



		std::shared_ptr<Resource> Engine::ResourceManagement::Resources::FindAsset(std::string assetPath)
		{
			std::shared_ptr<Resource> resourcePointer = NULL;

			try
			{
				if (_loadedAssets.count(assetPath))
				{
					resourcePointer = _loadedAssets[assetPath];
				}
				else
				{
					if (_resourceLocationFound || FindResourceFolder())
					{
						std::string completeAssetPath = _resourceLocation + assetPath;

						std::fstream fileStream;
						fileStream.open(completeAssetPath);
						if (fileStream.is_open())
						{
							fileStream.close();

							std::string fileType = assetPath.substr(assetPath.find_last_of("."));
							switch (_stringToFileType.count(fileType) ? _stringToFileType.at(fileType) : UNSUPPORTED)
							{
								case UNSUPPORTED:
								{
									throw ErrorHandling::Exception("Could not load asset. File type \"" + fileType + "\" is not supported.");
								}break;
								case TXT: // Creates a new text resource and initialises it with its 'Load' function.
								{
									std::cout << "File is text: " << fileType << std::endl;
								}break;
								case FBX: // Creates a new mesh resource and initialises it with its 'Load' function.
								{
									std::cout << "File is a mesh: " << fileType << std::endl;
								}break;
								case MP3: // Creates a new audio resource and initialises it with its 'Load' function.
								{
									std::cout << "File is an audio clip: " << fileType << std::endl;
								}break;
								case PNG: // Creates a new texture resource and initialises it with its 'Load' function.
								{
									std::cout << "File is a texture: " << fileType << std::endl;
								}break;
								case SHADER: // Creates a new shader resource and initialises it with its 'Load' function.
								{
									std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>();
									shader->Load(completeAssetPath);

									_loadedAssets.insert(std::pair<std::string, std::shared_ptr<Resource>>(assetPath, shader));
									resourcePointer = shader;
								}break;
							}
						}
						else
						{
							throw ErrorHandling::Exception("Failed to load asset \"" + assetPath + "\".");
						}
					}
					else
					{
						throw ErrorHandling::Exception("Could not find the 'Resource' folder location.");
					}
				}
			}
			catch (ErrorHandling::Exception e)
			{
				e.Print();
			}

			return resourcePointer;
		}

		bool Engine::ResourceManagement::Resources::FindResourceFolder()
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