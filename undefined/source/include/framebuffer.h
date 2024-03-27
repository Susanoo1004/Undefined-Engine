#pragma once

#include <memory>

#include "service_locator.h"

#include "resources/texture.h"

#include "engine_debug/logger.h"

class Framebuffer
{
public:
    Framebuffer();
	~Framebuffer();

	template <size_t TextureNumber>
    static Framebuffer* Create(unsigned int width, unsigned int height);

    void RescaleFramebuffer(unsigned int width, unsigned int height);

	unsigned int Width;
	unsigned int Height;

	unsigned int FBO_ID;
	unsigned int RBO_ID;

	std::vector<std::shared_ptr<Texture>> RenderedTextures;
};

template <size_t TextureNumber>
Framebuffer* Framebuffer::Create(unsigned int width, unsigned int height)
{
    static_assert(TextureNumber < 32, "TextureNumber must be less than 32");

    unsigned int attachments[TextureNumber] = { 0 };

    Framebuffer* f = new Framebuffer();

    f->Width = width;
    f->Height = height;

    glGenFramebuffers(1, &f->FBO_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, f->FBO_ID);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &f->RBO_ID);
    glBindRenderbuffer(GL_RENDERBUFFER, f->RBO_ID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, f->Width, f->Height); // use a single renderbuffer object for both a depth AND stencil buffer.

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, f->RBO_ID);

    f->RenderedTextures.resize(TextureNumber);

    for (int i = 0; i < TextureNumber; i++)
    {
        f->RenderedTextures[i] = std::make_shared<Texture>(f->Width, f->Height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, f->RenderedTextures[i]->GetID(), 0);
        attachments[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    glDrawBuffers(TextureNumber, attachments);

    glBindFramebuffer(GL_FRAMEBUFFER, f->FBO_ID);
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::Error("Framebuffer is not complete! : {}", glGetError());
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return f;
}
