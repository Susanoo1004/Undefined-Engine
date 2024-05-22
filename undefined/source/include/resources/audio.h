#pragma once
#include "resources/resource.h"
#include <AL/al.h>
#include <string>
#include <refl.hpp>

class Audio : public Resource
{
public:
	Audio(const char* filename);
	~Audio();
	
	char* GetData();
	ALushort GetChannel();
	ALushort GetBPS();
	ALint GetSampleRate();
	ALint GetSize();
	std::string GetName();

private:
	char* mData = nullptr;
	ALushort mChannel = 0, mBps = 0;
	ALint mSampleRate = 0, mSize = 0;

	friend struct refl_impl::metadata::type_info__ <Audio>;

	char* LoadWAV(const char* fn, ALushort& chan, ALint& samplerate, ALushort& bps, ALint& size);
	std::string mName;
};

REFL_AUTO(type(Audio, bases<Resource>),
	field(mName),
	field(mChannel),
	field(mBps),
	field(mSampleRate)
	);
