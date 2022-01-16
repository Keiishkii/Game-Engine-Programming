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
		/**	The AudioClip is a type of resource, its used to store the data from audio files. Inparticular .ogg files.  	*/
		struct AudioClip : Resource
		{
		private:
			std::shared_ptr<Audio::AudioBuffer> _audioBuffer;
		public:


		private:
		public:
			virtual void Load(const std::string& resourcesDirectory, const std::string& subPath) override;

			std::shared_ptr<Audio::AudioBuffer> GetBuffer();
			ALuint GetBufferID();
			ALenum GetFormat();
		};
	}
}