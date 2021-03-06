#include <memory>
#include <al.h>
#include <alc.h>

#include "Component.h"

namespace Engine
{
	namespace ResourceManagement { struct AudioClip; }

	namespace Components
	{
		/**	The AudioSource is a child of Component, it is used play audio in the scene. This object directly syncs with the OpenAL audio source allowing for 3D audio displacement to occur.  	*/
		struct AudioSource : Component
		{
		private:
			ALuint _sourceID;

			bool _playOnStart = false;
			bool _looping = false;

			std::shared_ptr<ResourceManagement::AudioClip> _audioClip;
		public:


		private:
			virtual void Start() override;
			virtual void Update() override;
		public:
			virtual void Initialise(const std::shared_ptr<Component>& self, const std::shared_ptr<Engine::Entity>& entity) override;
			~AudioSource();

			void PlayAudioClip();

			void SetAudioClip(std::shared_ptr<ResourceManagement::AudioClip> audioClip);
			void PlayOnStart(bool playOnStart);
			void Looping(bool playOnStart);
		};
	}
}