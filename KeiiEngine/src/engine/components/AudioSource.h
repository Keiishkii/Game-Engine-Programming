#include <memory>
#include <al.h>
#include <alc.h>

#include "Component.h"

namespace Engine
{
	namespace ResourceManagement { struct AudioClip; }

	namespace Components
	{
		struct AudioSource : Component
		{
		private:
			ALuint _sourceID;

			bool _playOnStart;
			std::shared_ptr<ResourceManagement::AudioClip> _audioClip;
		public:


		private:
			virtual void Start() override;
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			~AudioSource();

			void PlayAudioClip();

			void SetAudioClip(std::shared_ptr<ResourceManagement::AudioClip> audioClip);
			void PlayOnStart(bool playOnStart);
		};
	}
}