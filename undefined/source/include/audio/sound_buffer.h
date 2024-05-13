#pragma once

#include <AL/al.h>
#include <vector>
#include "resources/audio.h"
#include <memory>

struct ALCbuffer;

class SoundBuffer
{
public:
	static SoundBuffer* Get();
	
	ALuint AddSoundEffect(std::shared_ptr<Audio> filename);
	bool RemoveSoundEffect(const ALuint& buffer);

	static inline std::vector<const char*> audioFilesName;

private:
	SoundBuffer();
	~SoundBuffer();

	std::vector<ALuint> mSoundEffectBuffers;
};