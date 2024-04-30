#pragma once

#include <AL/al.h>
#include <vector>

struct ALCbuffer;

class SoundBuffer
{
public:
	static SoundBuffer* Get();
	
	ALuint AddSoundEffect(const char* filename);
	bool RemoveSoundEffect(const ALuint& buffer);

	static inline std::vector<const char*> audioFilesName;

private:
	SoundBuffer();
	~SoundBuffer();

	std::vector<ALuint> mSoundEffectBuffers;
};