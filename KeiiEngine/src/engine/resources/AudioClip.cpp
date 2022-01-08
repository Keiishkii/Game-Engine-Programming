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
	

			short* decodedAudio = NULL;
			int channels = 0, sampleRate = 0;

			int sampleCount = stb_vorbis_decode_filename(path.c_str(), &channels, &sampleRate, &decodedAudio);
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
				_audioBuffer->SetData(decodedAudio, sampleCount);
			}

			free(decodedAudio);
		}


		ALuint AudioClip::GetBufferID()	{ return _audioBuffer->GetID(); }
		std::shared_ptr<Audio::AudioBuffer> AudioClip::GetBuffer()	{ return _audioBuffer; }
		ALenum AudioClip::GetFormat()	{ return _audioBuffer->GetFormat(); }
	}
}