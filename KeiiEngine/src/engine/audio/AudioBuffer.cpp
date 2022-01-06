#include "AudioBuffer.h"
#include "AudioManager.h"
#include "engine/error-handling/Exception.h"


using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace Audio
	{
		AudioBuffer::AudioBuffer()
		{
			alGenBuffers(1, &_ID);

			if (AudioManager::AudioErrorEncountered()) [[unlikely]]
			{
				throw Exception("Failed to generate 'Audio Buffer' ID");
			}
		}

		ALuint AudioBuffer::GetID()
		{
			if (_dirty) [[unlikely]]
			{
				alBufferData(_ID, _format, &_data.at(0), (ALsizei)(_data.size()), _frequency);

				_dirty = false;
			}

 			return _ID;
		}


		void AudioBuffer::SetData(short* audioData, int sampleCount)
		{
			_data.resize(sampleCount * 2);
			memcpy(&(_data.at(0)), audioData, _data.size());

			_dirty = true;
		}

		void AudioBuffer::SetFrequency(ALsizei frequency) 
		{ 
			_frequency = frequency;

			_dirty = true;
		}

		void AudioBuffer::SetFormat(ALsizei format) 
		{ 
			_format = format;

			_dirty = true;
		}

		std::vector<char>& AudioBuffer::GetData() { return _data; }
	}
}