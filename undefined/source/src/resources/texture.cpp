#include "resources/texture.h"

#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

#include "logger/logger.h"

Texture::Texture(const char* filepath, bool isFlipped)
{
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	stbi_set_flip_vertically_on_load(isFlipped);

	int channelCount;
	const unsigned char* data = stbi_load(filepath, &mWidth, &mHeight, &channelCount, 0);

	if (data)
	{
		GLenum format = 0;

		if (channelCount == 1)
		{
			format = GL_RED;
		}
		else if (channelCount == 3)
		{
			format = GL_RGB;
		}
		else if (channelCount == 4)
		{
			format = GL_RGBA;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Logger::Warning("Failed to load {} texture", filepath);
	}

	stbi_image_free((void*)data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mID);
}

const unsigned int Texture::GetID()
{
	return mID;
}

const void Texture::SetID(unsigned int newID)
{
	mID = newID;
}

const unsigned int Texture::GetWidth()
{
	return mWidth;
}

const unsigned int Texture::GetHeight()
{
	return mHeight;
}

bool Texture::IsValid()
{
	return (mWidth > 0 && mHeight > 0);
}
