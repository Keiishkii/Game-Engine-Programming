#include <vector>
#include <al.h>
#include <alc.h>

namespace Engine
{
	namespace Audio
	{
		/**	The AudioBuffer is a class used to store and upload data to OpenAL's audio state-machine.  	*/
		struct AudioBuffer
		{
		private:
			bool _dirty = false;
			ALuint _ID = 0;

			std::vector<char> _data;

			ALenum _format = 0;
			ALsizei _frequency = 0;
		public:


		private:
		public:
			AudioBuffer();

			ALuint GetID();
			ALenum GetFormat();
			std::vector<char>& GetData();

			void SetFrequency(ALsizei frequency);
			void SetFormat(ALsizei format);
			void SetData(short* audioData, int sampleCount);
		};
	}
}