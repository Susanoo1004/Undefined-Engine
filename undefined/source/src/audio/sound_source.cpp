#include "audio/sound_source.h"
#include "engine_debug/logger.h"

SoundSource::SoundSource()
{
	alGenSources(1, &mSource);
	alSourcef(mSource, AL_PITCH, mPitch);
	alSourcef(mSource, AL_GAIN, mGain);
	alSource3f(mSource, AL_POSITION, mPostition.x, mPostition.y, mPostition.z);
	alSource3f(mSource, AL_VELOCITY, mVelocity.x, mVelocity.y, mVelocity.z);
	alSourcei(mSource, AL_LOOPING, mLoop);
	alSourcei(mSource, AL_BUFFER, mBuffer);
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

	Vector3 test(1.f);
	ALint state = AL_PLAYING;
	Logger::Info("Playing sound {}", mBuffer);
	//while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
	//{
	//	//Logger::Info("Currently playing sound");
	//	Logger::Debug(test, test);
	//	alGetSourcei(mSource, AL_SOURCE_STATE, &state);
	//}
	//Logger::Info("Stopped playing sound");

	//alDeleteSources(1, &mSource);
	//alDeleteBuffers(1, &buffer);
}
