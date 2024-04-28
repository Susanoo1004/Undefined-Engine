#include <AL/al.h>

#include "audio/sound_device.h"
#include "engine_debug/logger.h"

SoundDevice* SoundDevice::Get()
{
	static SoundDevice* soundDevice = new SoundDevice();
	return soundDevice;
}

SoundDevice::SoundDevice()
{
	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT"))
	{
		name = alcGetString(mALCDevice, ALC_DEFAULT_ALL_DEVICES_SPECIFIER); //Get device name
	}

	if (!name && alcGetError(nullptr) != ALC_DEVICE_SPECIFIER)
	{
		name = alcGetString(mALCDevice, ALC_DEVICE_SPECIFIER);
	}

	mALCDevice = alcOpenDevice(name); //Get default device (nullptr = default)
	if (!mALCDevice)
	{
		Logger::Warning("Failed to get sound device");
	}

	mALCContext = alcCreateContext(mALCDevice, nullptr); //Create context
	if(!mALCContext)
	{
		Logger::Warning("Failed to set sound context");
	}

	if (!alcMakeContextCurrent(mALCContext)) //Make context current
	{
		Logger::Warning("Failed to make context current");
	}

	Logger::Info("Opened {}", name);
}

SoundDevice::~SoundDevice()
{
}
