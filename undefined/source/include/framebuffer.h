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
    static Framebuffer* Create();

    void RescaleFramebuffer(float width, float height);

	unsigned int Width;
	unsigned int Height;

	unsigned int FBO_ID;
	unsigned int RBO_ID;

	std::vector<std::shared_ptr<Texture>> RenderedTextures;
};

template <size_t TextureNumber>
Framebuffer* Framebuffer::Create()
{
    static_assert(TextureNumber < 32, "TextureNumber must be less than 32");
    Framebuffer* f = new Framebuffer();
    Window* w = ServiceLocator::Get<Window>();
    unsigned int attachments[TextureNumber] = { 0 };

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &f->RBO_ID);
    glBindRenderbuffer(GL_RENDERBUFFER, f->RBO_ID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, f->Width, f->Height); // use a single renderbuffer object for both a depth AND stencil buffer.

    glGenFramebuffers(1, &f->FBO_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, f->FBO_ID);

    f->RenderedTextures.resize(TextureNumber);

    for (int i = 0; i < TextureNumber; i++)
    {
        f->RenderedTextures[i] = std::make_shared<Texture>(w->Width, w->Height);
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

    return f;
}
