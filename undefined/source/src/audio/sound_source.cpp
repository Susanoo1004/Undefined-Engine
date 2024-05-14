#include "audio/sound_source.h"
#include "engine_debug/logger.h"
#include "audio/sound_buffer.h"

#define CHECK_AL_ERROR() Logger::Info("{}", alGetString(alGetError()));

SoundSource::SoundSource()
{
}

SoundSource::~SoundSource()
{
	for (auto&& p : mSoundEffectSource)
	{
		alDeleteSources(1, &p.second);
	}
	mSoundEffectSource.clear();
}

void SoundSource::Play(const ALuint buffer)
{
	if (mSoundEffectSource.size() == 0)
	{
		ALuint source = CreateSource(buffer);
		mSoundEffectSource.emplace(buffer, source);
		alSourcei(source, AL_BUFFER, (ALint)buffer);
		alGetSourcei(source, AL_SOURCE_STATE, &mState);
		if (mState != AL_PLAYING && alGetError() == AL_NO_ERROR)
		{
			alSourcePlay(source);
		
			std::string name = SoundBuffer::audioFilesName[buffer - 1];
			std::string newName = name.substr(name.find_last_of("/") + 1);
			Logger::Info("Playing {}", newName);
		}
	}

	else if (!ContainsBuffer(buffer))
	{
		ALuint source = CreateSource(buffer);
		mSoundEffectSource.emplace(buffer, source);
		alSourcei(source, AL_BUFFER, (ALint)buffer);
		alGetSourcei(source, AL_SOURCE_STATE, &mState);
		if (mState != AL_PLAYING && alGetError() == AL_NO_ERROR)
		{
			alSourcePlay(source);

			std::string name = SoundBuffer::audioFilesName[buffer - 1];
			std::string newName = name.substr(name.find_last_of("/") + 1);
			Logger::Info("Playing {}", newName);
		}
	}
}

void SoundSource::Pause(const ALuint buffer)
{
	ALuint source = GetSource(buffer);
	alGetSourcei(source, AL_SOURCE_STATE, &mState);
	if (mState == AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		alSourcePause(source);

		std::string name = SoundBuffer::audioFilesName[buffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Paused sound {}", newName);
	}
}

void SoundSource::Resume(const ALuint buffer)
{
	ALuint source = GetSource(buffer);
	alGetSourcei(source, AL_SOURCE_STATE, &mState);
	if (mState == AL_PAUSED && alGetError() == AL_NO_ERROR)
	{
		alSourcePlay(source);
		std::string name = SoundBuffer::audioFilesName[buffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Resumed {}", newName);
	}
}

void SoundSource::Stop(const ALuint buffer)
{
	ALuint source = GetSource(buffer);
	alGetSourcei(source, AL_SOURCE_STATE, &mState);
	if (mState != AL_STOPPED && alGetError() == AL_NO_ERROR)
	{
		alSourceStop(source);
		std::string name = SoundBuffer::audioFilesName[buffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Stopped playing {}", newName);
	}
}

void SoundSource::Restart(const ALuint buffer)
{
	ALuint source = GetSource(buffer);
	alGetSourcei(source, AL_SOURCE_STATE, &mState);
	if (mState != AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		alSourceRewind(source);
		alSourcePlay(source);
		std::string name = SoundBuffer::audioFilesName[buffer - 1];
		std::string newName = name.substr(name.find_last_of("/") + 1);
		Logger::Info("Restarted {}", newName);
	}
}

void SoundSource::SetPosition(ALuint buffer, const Vector3& position)
{
	alSource3f(GetSource(buffer), AL_POSITION, position.x, position.y, position.z);
}

void SoundSource::SetVelocity(ALuint buffer, const Vector3& velocity)
{
	alSource3f(buffer, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

void SoundSource::SetVolume(ALuint buffer, const float volume)
{
	alSourcef(GetSource(buffer), AL_GAIN, volume);
}

void SoundSource::SetSpeed(ALuint buffer, const float pitch)
{
	alSourcef(GetSource(buffer), AL_PITCH, pitch);
}

void SoundSource::SetLoop(ALuint buffer, const bool shouldLoop)
{
	alSourcei(GetSource(buffer), AL_LOOPING, shouldLoop);
}

ALuint SoundSource::CreateSource(ALuint buffer)
{
	ALuint source;
	alGenSources(1, &source);
	alSourcef(mSource, AL_PITCH, mPitch);
	alSourcef(mSource, AL_GAIN, mGain);
	alSource3f(mSource, AL_POSITION, mPostition.x, mPostition.y, mPostition.z);
	alSource3f(mSource, AL_VELOCITY, mVelocity.x, mVelocity.y, mVelocity.z);
	alSourcei(mSource, AL_LOOPING, mLoop);
	alSourcei(mSource, AL_BUFFER, buffer);
	
	return source;
}

ALuint SoundSource::GetSource(ALuint buffer)
{
	auto&& p = mSoundEffectSource.find(buffer);

	if (p == mSoundEffectSource.end())
	{
		return 0;
	}

	return p->second;
}

bool SoundSource::ContainsBuffer(ALuint buffer)
{
	return mSoundEffectSource.find(buffer) != mSoundEffectSource.end();
}
