#include "audio/sound_buffer.h"

#include <AL/alext.h>
#include <inttypes.h>
#include "engine_debug/logger.h"
#include <algorithm>

SoundBuffer* SoundBuffer::Get()
{
	static SoundBuffer* soundBuffer = new SoundBuffer();
	return soundBuffer;
}

ALuint SoundBuffer::AddSoundEffect(const char* filename)
{
	ALenum err, format;
	ALuint buffer;
	short* membuf;
	ALsizei num_bytes;
	ALsizei samplerate;

	//tout gober

	//num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);
	buffer = 0;
	alGenBuffers(1, &buffer);
	//alBufferData(buffer, format, membuf, num_bytes, samplerate);

	err = alGetError();
	if (err != AL_NO_ERROR)
	{
		Logger::Error("OpenAL Error: {}", alGetString(err));
		if (buffer && alIsBuffer(buffer))
		{
			alDeleteBuffers(1, &buffer);
		}

		return 0;
	}

	mSoundEffectBuffers.push_back(buffer);  // add to the list of known buffers

	return buffer;
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
	mSoundEffectBuffers.clear();
}
