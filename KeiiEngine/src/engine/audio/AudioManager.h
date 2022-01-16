#include "glew.h"
#include <memory>
#include <al.h>
#include <alc.h>


namespace Engine
{
	struct Core;

	namespace ResourceManagement { struct AudioClip; }
	namespace Audio
	{
		/**	The AudioManager is a class required for the instantiation and safe disposal of OpenAL's audio state machine.  	*/
		struct AudioManager
		{
		private:
			std::weak_ptr<Engine::Core> _core;

			std::shared_ptr<ALCdevice*> _device;
			std::shared_ptr<ALCcontext*> _context;
		public:


		private:
		public:
			static bool AudioErrorEncountered();

			AudioManager(std::shared_ptr<Engine::Core> core);
			~AudioManager();

			//void PlayAudioClip(std::shared_ptr<ResourceManagement::AudioClip> audioClip);
			//void PlayAudioClip(std::shared_ptr<ResourceManagement::AudioClip> audioClip, float volume);
		};
	}
}