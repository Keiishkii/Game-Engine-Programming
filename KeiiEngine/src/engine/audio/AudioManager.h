#include "glew.h"
#include <memory>
#include <al.h>
#include <alc.h>


namespace Engine
{
	struct Core;

	namespace Audio
	{
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
		};
	}
}