#pragma once

#include "resources/resource.h"
#include "utils/flag.h"

class UNDEFINED_ENGINE Texture : public Resource
{
public:
	Texture(const char* filepath);
	~Texture();

	const unsigned int GetID();
	bool isValid();

private:
	unsigned int mID;
	int mWidth;
	int mHeight;
};