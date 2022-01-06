#define STB_DEFINE
#define STB_ONLY

#include "stb/stb_vorbis.h"

#include "AudioClip.h"
#include "engine/audio/AudioBuffer.h"
#include "engine/error-handling/Exception.h"


using Engine::ErrorHandling::Exception;

namespace Engine
{
	namespace ResourceManagement
	{
		void AudioClip::Load(const std::string& resourcesDirectory, const std::string& subPath)
		{
			std::string path = resourcesDirectory + subPath;
	

			short* audioData = NULL;
			int channels = 0, sampleRate = 0;

			size_t sampleCount = stb_vorbis_decode_filename(path.c_str(), &channels, &sampleRate, &audioData);
			sampleCount = sampleCount - sampleCount % 4;

			if (sampleCount == -1)
			{
				throw Exception("Failed to load texture: " + subPath);
			}
			else
			{
				_audioBuffer = std::make_shared<Audio::AudioBuffer>();

				_audioBuffer->SetFormat((channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
				_audioBuffer->SetFrequency(sampleRate);
				_audioBuffer->SetData(audioData, sampleCount);
			}

			free(audioData);
		}


		ALuint AudioClip::GetBufferID()
		{
			return _audioBuffer->GetID();
		}
	}
}