#pragma once

#include <AL/al.h>

#include <toolbox/Vector3.h>

#include "utils/utils.h"

class SoundSource
{
public:
	SoundSource();
	UNDEFINED_ENGINE ~SoundSource();

	void Play(ALuint buffer);
	
private:
	ALuint mBuffer = 0;
	ALuint mSource;
	
	Vector3 mPostition = Vector3(1.f, 1.f, 1.f);
	Vector3 mVelocity = Vector3(1.f, 1.f, 1.f);

	float mPitch = 1.f;
	float mGain = 1.f;
	
	bool mLoop = false;
};