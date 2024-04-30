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

char* loadWAV(const char* fn, unsigned short& chan, int& samplerate, unsigned short& bps, int& size)
{
	std::ifstream file(fn, std::ios::in | std::ios::binary | std::ios::ate);
	int fileSize = file.tellg();
	file.seekg(0);

	if (!file.good())
	{
		Logger::Warning("File {} could not be open", fn);
	}

	char buffer[4];
	file.read(buffer, 4);

	if (strncmp(buffer, "RIFF", 4) == 0)
	{
		for (size_t i = 12; i < fileSize; i++)
		{
			if (strncmp(buffer, "fmt ", 4) == 0)
			{
				file.seekg(i + 8);
				file.read((char*)&chan, 2); //Number of channels
				file.read((char*)&samplerate, 4); //Sample rate
				Logger::Debug("{}", (int)file.cur);
				file.seekg(i + 20);
				file.read((char*)&bps, 2); //Bits per sample
			}
			if (strncmp(buffer, "data", 4) == 0)
			{
				file.seekg(i + 2);
				file.read((char*)&size, 4); //size
				char* data = new char[size];
				file.read(data, size);
				return data;
			}
			file.read(buffer, 4);
			file.seekg(i);
		}
	}
	return NULL;
}

ALuint SoundBuffer::AddSoundEffect(const char* filename)
{
	ALenum err;
	ALushort channel, bps;
	ALint sampleRate, size;
	ALuint bufferid, format;

	char* data = loadWAV(filename, channel, sampleRate, bps, size);

	if (channel == 1)
	{
		if (bps == 8)
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
		if (bps == 8)
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
	alBufferData(bufferid, format, data, size, sampleRate);

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
	audioFilesName.push_back(filename);
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
