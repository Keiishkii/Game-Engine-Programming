#include <iostream>

#include "AudioManager.h"
#include "engine/resources/AudioClip.h"
#include "engine/error-handling/Exception.h"

using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace Audio
	{
		bool AudioManager::AudioErrorEncountered()
		{
			bool errorFound = false;
			ALenum error = alGetError();

			if (error != AL_NO_ERROR)
			{
				errorFound = true;

				std::cout << "Audio Error Found: ";
				switch (error)
				{
					case ALC_INVALID_DEVICE: 
					{
						std::cout << "Invalid Device" << std::endl;
					} break;
					case ALC_INVALID_CONTEXT: 
					{
						std::cout << "Invalid Context" << std::endl;
					} break;
					case ALC_INVALID_ENUM:
					{
						std::cout << "Invalid Enum" << std::endl;
					} break;
					case ALC_INVALID_VALUE:
					{
						std::cout << "Invalid Value" << std::endl;
					} break;
					case AL_OUT_OF_MEMORY:
					{
						std::cout << "Out Of Memory" << std::endl;
					} break;
				}
			}

			return errorFound;
		}

		AudioManager::AudioManager(std::shared_ptr<Engine::Core> core)
		{
			_device = std::make_shared<ALCdevice*>();
			*_device = alcOpenDevice(NULL);

			if (!_device || !*_device)
			{
				throw Exception("'Audio Device' not found.");
			}
			else
			{
				_context = std::make_shared<ALCcontext*>();
				*_context = alcCreateContext(*_device, NULL);

				if (!_context || !*_context)
				{
					alcCloseDevice(*_device);

					throw Exception("'Audio Context' not found.");
				}
				else
				{
					if (!alcMakeContextCurrent(*_context))
					{
						alcDestroyContext(*_context);
						alcCloseDevice(*_device);

						throw Exception("'Could not make context current.");
					}
				}
			}
		}


		/*void AudioManager::PlayAudioClip(std::shared_ptr<ResourceManagement::AudioClip> audioClip)
		{
			if (audioClip && !Audio::AudioManager::AudioErrorEncountered()) [[likely]]
			{
				ALuint sourceID;
				alGenSources(1, &sourceID);


				alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
				alSource3f(sourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);

				alSourcei(sourceID, AL_BUFFER, audioClip->GetBufferID());

				alSourcePlay(sourceID);


				alDeleteSources(1, &sourceID);
			}
		}*/


		AudioManager::~AudioManager()
		{
			alcMakeContextCurrent(NULL);
			alcDestroyContext(*_context);
			alcCloseDevice(*_device);
		}
	}
}