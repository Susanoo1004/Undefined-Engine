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

    /// <summary>
    /// Rescale the framebuffer
    /// </summary>
    /// <param name="width">: New width of the framebuffer</param>
    /// <param name="height">: New height of the framebuufer</param>
    void RescaleFramebuffer(unsigned int width, unsigned int height);

	/// <summary>
	/// Width of the window
	/// </summary>
	unsigned int Width;
	/// <summary>
	/// Height of the window
	/// </summary>
	unsigned int Height;

	/// <summary>
	/// Framebuffer ID
	/// </summary>
	unsigned int FBO_ID;
	/// <summary>
	/// Renderbuffer Id
	/// </summary>
	unsigned int RBO_ID;

	/// <summary>
	/// stdd::vector to store the textures usefull for the framebuffer
	/// </summary>
	std::vector<std::unique_ptr<Texture>> FramebufferTextures;

private:
    /// <summary>
    /// Pointer to our Renderer to simplify the calls from the ServiceLocator
    /// </summary>
    Renderer* mRenderer = nullptr;

public:
    /// <summary>
    /// Create a new 
    /// </summary>
    /// <typeparam name="TextureNumber">: Number of textures in the framebuffer</typeparam>
    /// <param name="width">: Base width of the framebuffer</param>
    /// <param name="height">: Base height of the framebuffer</param>
    /// <returns></returns>
    template <size_t TextureNumber>
    static Framebuffer* Create(unsigned int width, unsigned int height);
};

template <size_t TextureNumber>
Framebuffer* Framebuffer::Create(unsigned int width, unsigned int height)
{
    static_assert(TextureNumber < 32, "TextureNumber must be less than 32");

    unsigned int attachments[TextureNumber] = { 0 };

    Framebuffer* f = new Framebuffer();

    f->Width = width;
    f->Height = height;

    Renderer* mRenderer = ServiceLocator::Get<Renderer>();

    mRenderer->GenerateFramebuffer(1, &f->FBO_ID);
    mRenderer->BindFramebuffer(GL_FRAMEBUFFER, f->FBO_ID);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    mRenderer->GenerateRenderbuffer(1,  &f->RBO_ID);
    mRenderer->BindRenderbuffer(f->RBO_ID);
    mRenderer->SetRenderBufferStorageData(GL_DEPTH24_STENCIL8, f->Width, f->Height); // use a single renderbuffer object for both a depth AND stencil buffer.

    mRenderer->BindRenderbufferToFramebuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, f->RBO_ID);

    f->FramebufferTextures.resize(TextureNumber);

    for (int i = 0; i < TextureNumber; i++)
    {
        if (i == 0)
        {
            f->FramebufferTextures[0] = std::make_unique<Texture>(f->Width, f->Height);
        }

        else
        {
            f->FramebufferTextures[i] = std::make_unique<Texture>(f->Width, f->Height, GL_R32I, GL_RED_INTEGER);
        }

        mRenderer->BindTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, f->FramebufferTextures[i]->GetID());
        attachments[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    glDrawBuffers(TextureNumber, attachments);

    mRenderer->BindFramebuffer(GL_FRAMEBUFFER, f->FBO_ID);
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::Error("Framebuffer is not complete! : {}", glGetError());
    }

    mRenderer->BindFramebuffer(GL_FRAMEBUFFER, 0);

    return f;
}