#pragma once

#include <string>
#include <filesystem>
#include <array>

#include "resources/resource.h"
#include "utils/flag.h"

class UNDEFINED_ENGINE Texture : public Resource
{
public:
	Texture(const char* filepath, bool isFlipped = false);
	~Texture();

	const unsigned int GetID();
	const void SetID(unsigned int newID);
	const unsigned int GetWidth();
	const unsigned int GetHeight();
	bool IsValid();

	static unsigned int LoadCubeMap(std::vector<std::string> faces);

private:
	unsigned int mID;
	int mWidth;
	int mHeight;
};