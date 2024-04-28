#pragma once
#include "audio/sound_context.h"

struct ALCdevice;
struct ALCcontext;

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