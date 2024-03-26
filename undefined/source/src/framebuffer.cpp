#include "framebuffer.h"

Framebuffer::Framebuffer()
{
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &FBO_ID);
}

void Framebuffer::RescaleFramebuffer(float width, float height)
{
	Width = width;
	Height = height;

	for (int i = 0; i < RenderedTextures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, RenderedTextures[i]->GetID());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderedTextures[i]->GetID(), 0);
	}

	glBindRenderbuffer(GL_RENDERBUFFER, RBO_ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO_ID);
}