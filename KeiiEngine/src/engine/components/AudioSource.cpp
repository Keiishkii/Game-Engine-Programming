#include <iostream>

#include "AudioSource.h"
#include "engine/audio/AudioManager.h"
#include "engine/error-handling/Exception.h"
#include "engine/resources/AudioClip.h"


using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace Components
	{
		void AudioSource::Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity)
		{
			alGenSources(1, &_sourceID);

			if (alGetError() != AL_NO_ERROR) [[unlikely]]
			{
				throw Exception("Failed to generate 'Audio Source' ID");
			}
		}

		void AudioSource::Start()
		{
			if (_playOnStart)
			{
				PlayAudioClip();
			}
		}



		void AudioSource::PlayAudioClip()
		{
			std::cout << "Play Audio Clip" << std::endl;

			if (_audioClip && !Audio::AudioManager::AudioErrorEncountered()) [[likely]]
			{
				std::cout << "SOUND!" << std::endl;
				alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
				alSource3f(_sourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);
				alSourcei(_sourceID, AL_BUFFER, _audioClip->GetBufferID());
				//alSourcef(_sourceID, AL_PITCH, variance);
				alSourcef(_sourceID, AL_GAIN, 1);
				alSourcePlay(_sourceID);
			}
		}



		void AudioSource::PlayOnStart(bool playOnStart)
		{ 
			_playOnStart = playOnStart;
		}

		void AudioSource::SetAudioClip(std::shared_ptr<ResourceManagement::AudioClip> audioClip)
		{
			_audioClip = audioClip;
		}
	}
}