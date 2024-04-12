#include "framebuffer.h"

Framebuffer::Framebuffer()
	: FBO_ID(0), RBO_ID(0), Height(0), Width(0), mRenderer(mRenderer = ServiceLocator::Get<Renderer>())
{
}

Framebuffer::~Framebuffer()
{
	mRenderer->DeleteFramebuffers(1, &FBO_ID);
	mRenderer->DeleteRenderbuffers(1, &FBO_ID);
}

void Framebuffer::RescaleFramebuffer(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;

	mRenderer->BindFramebuffer(GL_FRAMEBUFFER, FBO_ID);

	for (int i = 0; i < RenderedTextures.size(); i++)
	{
		mRenderer->BindTexture(RenderedTextures[i]->GetID());
		if (i == 0)
		{
			// TODO add to renderer
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)Width , (GLsizei)Height, 0, GL_RGB, GL_UNSIGNED_BYTE, RenderedTextures[i]->Data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, (GLsizei)Width, (GLsizei)Height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, RenderedTextures[i]->Data);
		}

		mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		mRenderer->SetTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
		mRenderer->BindTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, RenderedTextures[i]->GetID());
	}

	mRenderer->BindRenderbuffer(RBO_ID);
	mRenderer->SetRenderBufferStorageData(GL_DEPTH24_STENCIL8, (float)Width, (float)Height);
	mRenderer->BindRenderbufferToFramebuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, RBO_ID);
	
	mRenderer->BindFramebuffer(GL_FRAMEBUFFER, 0);
}