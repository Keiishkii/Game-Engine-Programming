#include "Resource.h"
#include <al.h>
#include <alc.h>

namespace Engine
{
	namespace Audio 
	{
		struct AudioBuffer;
	}
	
	namespace ResourceManagement
	{
		struct AudioClip : Resource
		{
		private:
			std::shared_ptr<Audio::AudioBuffer> _audioBuffer;
		public:


		private:
		public:
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;

			ALuint GetBufferID();
		};
	}
}