#pragma once

#include <AL/al.h>

#include <toolbox/Vector3.h>

class SoundSource
{
public:
	SoundSource();
	~SoundSource();

	void Play(const ALuint buffer);
	
private:
	ALuint mBuffer = 0;
	ALuint mSource;
	
	Vector3 mPostition = Vector3(1.f);
	
	float mPitch = 1.f;
	float mGain = 1.f;
	
	bool mLoop = false;
};