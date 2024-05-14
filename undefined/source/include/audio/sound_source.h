#pragma once

#include <AL/al.h>

#include <unordered_map>
#include <toolbox/Vector3.h>

#include "utils/utils.h"

class SoundSource
{
public:
	SoundSource();
	UNDEFINED_ENGINE ~SoundSource();

	void Play(const ALuint buffer);
	void Pause(ALuint buffer);
	void Resume(ALuint buffer);
	void Stop(ALuint buffer);
	void Restart(ALuint buffer);

	void SetPosition(ALuint buffer, const Vector3& position);
	void SetVelocity(ALuint buffer, const Vector3& velocity);
	void SetVolume(ALuint buffer, const float volume);
	void SetSpeed(ALuint buffer, const float pitch);
	void SetLoop(ALuint buffer, const bool shouldLoop);

private:
	ALuint CreateSource(ALuint buffer);
	ALuint GetSource(ALuint buffer);
	bool ContainsBuffer(ALuint buffer);

	ALuint mBuffer = 0;
	ALuint mSource = 0;
	ALint mState = 0;

	Vector3 mPostition = Vector3(1.f, 1.f, 1.f);
	Vector3 mVelocity = Vector3(1.f, 1.f, 1.f);

	float mGain = 1.f;
	float mPitch = 1.f;
	
	bool mLoop = false;
	/// <summary>
	/// buffer, source
	/// </summary>
	std::unordered_map<ALuint, ALuint> mSoundEffectSource;
};