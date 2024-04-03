#include "resources/texture.h"

#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

#include "engine_debug/logger.h"

Texture::Texture(const unsigned int width, const unsigned int height)
	: mWidth(width), mHeight(height)
{
	mRenderer = ServiceLocator::Get<Renderer>();

	mRenderer->GenTexture(1, &mID);
	mRenderer->BindTexture(mID);

	mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
}

Texture::Texture(const char* filepath, bool isFlipped)
{
	mRenderer = ServiceLocator::Get<Renderer>();

	mRenderer->GenTexture(1, &mID);
	mRenderer->BindTexture(mID);

	stbi_set_flip_vertically_on_load(isFlipped);

	int channelCount;
	Data = stbi_load(filepath, &mWidth, &mHeight, &channelCount, 0);

	if (Data)
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

		mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, Data);
		mRenderer->GenerateMipMap(GL_TEXTURE_2D);
	}
	else
	{
		Logger::Warning("Failed to load {} texture", filepath);
	}

	stbi_image_free((void*)Data);
}

Texture::~Texture()
{
	mRenderer->DeleteTexture(1, &mID);
}

unsigned int Texture::GetID() const
{
	return mID;
}

void Texture::SetID(unsigned int newID)
{
	mID = newID;
}

unsigned int Texture::GetWidth() const
{
	return mWidth;
}

unsigned int Texture::GetHeight() const
{
	return mHeight;
}

bool Texture::IsValid() const
{
	return (mWidth > 0 && mHeight > 0);
}

unsigned int Texture::LoadCubeMap(const std::vector<std::string>& faces)
{
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			Logger::Debug("Cubemap texture {} loaded", faces[i].c_str());
		}
		else
		{
			Logger::Debug("Cubemap texture failed to load at path: {}", faces[i].c_str());
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
