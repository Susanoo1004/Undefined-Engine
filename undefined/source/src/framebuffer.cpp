#include "framebuffer.h"

Framebuffer::Framebuffer()
	: FBO_ID(0), RBO_ID(0), Height(0), Width(0)
{
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &FBO_ID);
	glDeleteRenderbuffers(1, &RBO_ID);
}

void Framebuffer::RescaleFramebuffer(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;

	glBindFramebuffer(GL_FRAMEBUFFER, FBO_ID);

	for (int i = 0; i < RenderedTextures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, RenderedTextures[i]->GetID());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (i == 0)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)Width, (GLsizei)Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderedTextures[0]->GetID(), 0);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, (GLsizei)Width, (GLsizei)Height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, RenderedTextures[i]->GetID(), 0);
		}
	}

	glBindRenderbuffer(GL_RENDERBUFFER, RBO_ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (GLsizei)Width, (GLsizei)Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO_ID);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}