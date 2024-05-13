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
	void Pause(ALuint buffer);
	void Resume(ALuint buffer);
	void Stop(ALuint buffer);
	void Restart(ALuint buffer);

	void SetPosition(const Vector3& position);
	void SetVelocity(const Vector3& velocity);
	void SetVolume(const float volume);
	void SetSpeed(const float pitch);
	void SetLoop(const bool shouldLoop);

private:
	ALuint mBuffer = 0;
	ALuint mSource = 0;
	ALint mState = 0;

	Vector3 mPostition = Vector3(1.f, 1.f, 1.f);
	Vector3 mVelocity = Vector3(1.f, 1.f, 1.f);

	float mGain = 1.f;
	float mPitch = 1.f;
	
	bool mLoop = false;
};