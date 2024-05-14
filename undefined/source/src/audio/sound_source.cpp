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
		
		std::string name = SoundBuffer::audioFilesName[mBuffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Playing {}", newName);
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
		alSourcePause(buffer);

		std::string name = SoundBuffer::audioFilesName[mBuffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Paused sound {}", newName);
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
		std::string name = SoundBuffer::audioFilesName[mBuffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Resumed {}", newName);
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
		alSourceStop(mSource);
		std::string name = SoundBuffer::audioFilesName[mBuffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Stopped playing {}", newName);
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
		alSourceRewind(mSource);
		alSourcePlay(mSource);
		std::string name = SoundBuffer::audioFilesName[mBuffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Restarted {}", newName);
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
