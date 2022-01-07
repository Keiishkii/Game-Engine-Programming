#include <iostream>

#include "AudioSource.h"
#include "Transform.h"
#include "Gizmo.h"
#include "engine/audio/AudioManager.h"
#include "engine/error-handling/Exception.h"
#include "engine/resources/ResourceManager.h"
#include "engine/resources/AudioClip.h"
#include "engine/resources/Texture.h"
#include "engine/Core.h"
#include "engine/Entity.h"


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

			Entity()->AddComponent<Gizmo>(Core()->ResourceManager()->FindAsset<ResourceManagement::Texture>("- textures/gizmo/audio_source.png"));
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
			if (_audioClip && !Audio::AudioManager::AudioErrorEncountered()) [[likely]]
			{
				alSourcei(_sourceID, AL_BUFFER, _audioClip->GetBufferID());

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


		AudioSource::~AudioSource()
		{
			alDeleteSources(1, &_sourceID);
		}
	}
}