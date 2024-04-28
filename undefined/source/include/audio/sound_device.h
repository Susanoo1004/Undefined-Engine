#pragma once
#include "audio/sound_context.h"
#include <AL/alc.h>

class SoundDevice
{
public:
	static SoundDevice* Get();

private:
	SoundDevice();
	~SoundDevice();

	ALCdevice* mALCDevice;
	ALCcontext* mALCContext;
};