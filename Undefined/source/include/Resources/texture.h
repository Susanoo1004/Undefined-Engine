#pragma once
#include "Resources/resource.h"

class Texture : public Resource
{
public:
	Texture(const char* filepath);
	~Texture();

	unsigned int GetID();

private:
	unsigned int mID;
	int mWidth;
	int mHeight;
};