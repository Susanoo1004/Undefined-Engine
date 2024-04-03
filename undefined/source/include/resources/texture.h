#pragma once

#include <string>
#include <filesystem>
#include <array>

#include "resources/resource.h"
#include "wrapper/renderer.h"
#include "service_locator.h"
#include "utils/flag.h"

class UNDEFINED_ENGINE Texture : public Resource
{
public:
	Texture(unsigned int width, unsigned int height);
	Texture(const char* filepath, bool isFlipped = false);
	~Texture();

	unsigned int GetID() const;
	void SetID(unsigned int newID);
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	bool IsValid() const;

	const void* Data;

private:
	unsigned int mID = 0;
	int mWidth = 0;
	int mHeight = 0;
	Renderer* mRenderer = nullptr;

public:
	static unsigned int LoadCubeMap(const std::vector<std::string>& faces);
};