#include <iostream>

#include "AudioSource.h"
#include "Transform.h"
#include "Gizmo.h"
#include "engine/audio/AudioManager.h"
#include "engine/error-handling/Exception.h"
#include "engine/error-handling/Debugger.h"
#include "engine/resources/ResourceManager.h"
#include "engine/resources/AudioClip.h"
#include "engine/resources/Texture.h"
#include "engine/Core.h"
#include "engine/Entity.h"


using Engine::ErrorHandling::Exception;
using Engine::ErrorHandling::Debugger;

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
				
			#if DEBUG
			{
				Entity()->AddComponent<Gizmo>(Core()->ResourceManager()->FindAsset<ResourceManagement::Texture>("- textures/gizmo/audio_source.png"));
			}
			#endif
		}

		void AudioSource::Start()
		{
			if (_playOnStart)
			{
				PlayAudioClip();
			}
		}

		void AudioSource::Update()
		{
			glm::vec3 position = Transform()->Position();
			alSource3f(_sourceID, AL_POSITION, position.x, position.y, position.z);
		}


		void AudioSource::PlayAudioClip()
		{
			if (_audioClip && _audioClip->GetBuffer() && !Audio::AudioManager::AudioErrorEncountered()) [[likely]]
			{
				if (_audioClip->GetFormat() == AL_FORMAT_STEREO16) [[unlikely]]
				{
					Debugger::PrintWarning("Audio file '" + _audioClip->GetName() + "' is of type 'AL_FORMAT_STEREO16' this will not work with spatial sound.");
				}

				alSourcei(_sourceID, AL_BUFFER, _audioClip->GetBufferID());
				
				alSourcePlay(_sourceID);
			}
		}


		void AudioSource::PlayOnStart(bool playOnStart)	{ _playOnStart = playOnStart; }
		void AudioSource::Looping(bool looping)	
		{ 
			alSourcei(_sourceID, AL_LOOPING, (looping) ? AL_TRUE : AL_FALSE);
		}

		void AudioSource::SetAudioClip(std::shared_ptr<ResourceManagement::AudioClip> audioClip)
		{
			_audioClip = audioClip;
		}


		AudioSource::~AudioSource()
		{
			alDeleteSources(1, &_sourceID);
		}
	}
}