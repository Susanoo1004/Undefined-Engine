#include "audio/sound_source.h"
#include "engine_debug/logger.h"
#include "audio/sound_buffer.h"

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

	alGetSourcei(mSource, AL_SOURCE_STATE, &mState);
	if (mState != AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		alSourcePlay(mSource);
		Logger::Info("Playing sound {}", SoundBuffer::audioFilesName[mBuffer - 1]);
	}
}

void SoundSource::Pause(const ALuint buffer)
{
	if (buffer != mBuffer)
	{
		mBuffer = buffer;
		alSourcei(mSource, AL_BUFFER, (ALint)mBuffer);
	}

	alGetSourcei(mSource, AL_SOURCE_STATE, &mState);
	if (mState == AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		alSourcePause(mSource);
		Logger::Info("Paused sound {}", SoundBuffer::audioFilesName[mBuffer - 1]);
	}
}

void SoundSource::Resume(const ALuint buffer)
{
	if (buffer != mBuffer)
	{
		mBuffer = buffer;
		alSourcei(mSource, AL_BUFFER, (ALint)mBuffer);
	}

	alGetSourcei(mSource, AL_SOURCE_STATE, &mState);
	if (mState == AL_PAUSED && alGetError() == AL_NO_ERROR)
	{
		alSourcePlay(mSource);
		Logger::Info("Resume sound {}", SoundBuffer::audioFilesName[mBuffer - 1]);
	}
}

void SoundSource::Stop(const ALuint buffer)
{
	if (buffer != mBuffer)
	{
		mBuffer = buffer;
		alSourcei(mSource, AL_BUFFER, (ALint)mBuffer);
	}

	alGetSourcei(mSource, AL_SOURCE_STATE, &mState);
	if (mState != AL_STOPPED && alGetError() == AL_NO_ERROR)
	{
		Logger::Info("Stopped playing sound {}", SoundBuffer::audioFilesName[mBuffer - 1]);
		alSourceStop(mSource);
	}
}

void SoundSource::Restart(const ALuint buffer)
{
	if (buffer != mBuffer)
	{
		mBuffer = buffer;
		alSourcei(mSource, AL_BUFFER, (ALint)mBuffer);
	}

	alGetSourcei(mSource, AL_SOURCE_STATE, &mState);
	if (mState != AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		Logger::Info("Restarted sound {}", SoundBuffer::audioFilesName[mBuffer - 1]);
		alSourceRewind(mSource);
		alSourcePlay(mSource);
	}
}

void SoundSource::SetPosition(const Vector3& position)
{
	mPostition = position;
}

void SoundSource::SetVelocity(const Vector3& velocity)
{
	mVelocity = velocity;
}

void SoundSource::SetVolume(const float volume)
{
	mGain = volume;
}

void SoundSource::SetSpeed(const float pitch)
{
	mPitch = pitch;
}

void SoundSource::SetLoop(const bool shouldLoop)
{
	mLoop = shouldLoop;
}
