#include "audio/sound_buffer.h"

#include <AL/alext.h>
#include <inttypes.h>
#include <algorithm>

#include "engine_debug/logger.h"
#include "resources/audio.h"

SoundBuffer* SoundBuffer::Get()
{
	static SoundBuffer* soundBuffer = new SoundBuffer();
	return soundBuffer;
}

ALuint SoundBuffer::AddSoundEffect(std::shared_ptr<Audio> filename)
{
	ALenum err = 0;
	ALuint bufferid = 0, format = 0;

	if (filename->GetChannel() == 1)
	{
		if (filename->GetBPS() == 8)
		{
			format = AL_FORMAT_MONO8;
		}
		else 
		{
			format = AL_FORMAT_MONO16;
		}
	}
	else
	{
		if (filename->GetBPS() == 8)
		{
			format = AL_FORMAT_STEREO8;
		}
		else 
		{
			format = AL_FORMAT_STEREO16;
		}
	}

	bufferid = 0;
	alGenBuffers(1, &bufferid);
	alBufferData(bufferid, format, filename->GetData(), filename->GetSize(), filename->GetSampleRate());

	err = alGetError();
	if (err != AL_NO_ERROR)
	{
		Logger::Error("OpenAL Error: {}", alGetString(err));
		if (bufferid && alIsBuffer(bufferid))
		{
			alDeleteBuffers(1, &bufferid);
		}

		return 0;
	}

	mSoundEffectBuffers.push_back(bufferid);  // add to the list of known buffers
	audioFilesName.push_back(filename->GetName());
	return bufferid;
}

bool SoundBuffer::RemoveSoundEffect(const ALuint& buffer)
{
	if (std::erase(mSoundEffectBuffers, buffer) > 0)
	{
		return true;
	}
	return false;
}

SoundBuffer::SoundBuffer()
{
	mSoundEffectBuffers.clear();
}

SoundBuffer::~SoundBuffer()
{
	alDeleteBuffers(mSoundEffectBuffers.size(), mSoundEffectBuffers.data());

	mSoundEffectBuffers.clear();
}
