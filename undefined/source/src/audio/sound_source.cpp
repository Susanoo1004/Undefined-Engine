#include "..\..\include\audio\sound_source.h"

SoundSource::SoundSource()
{
	alGenSources(1, &mSource);
	alSourcef(mSource, AL_PITCH, mPitch);
	alSourcef(mSource, AL_GAIN, mGain);
	alSourcef(mSource, AL_POSITION, (ALfloat)mPostition.x);
	alSourcef(mSource, AL_LOOPING, mLoop);
	alSourcef(mSource, AL_BUFFER, mBuffer);
}

SoundSource::~SoundSource()
{
	alDeleteSources(1, &mSource);
}

void SoundSource::Play(const ALuint buffer)
{
	if (buffer != mBuffer)
	{
		mBuffer = buffer;
		alSourcei(mSource, AL_BUFFER, (ALint)mBuffer);
	}

	alSourcePlay(mSource);
}
