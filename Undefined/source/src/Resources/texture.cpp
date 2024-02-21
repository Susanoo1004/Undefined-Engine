#include "resources/texture.h"

#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

Texture::Texture(const char* filepath)
{
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	int channelCount;
	stbi_set_flip_vertically_on_load(true);
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
		std::cout << "Failed to load " << filepath << " texture" << std::endl;
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
