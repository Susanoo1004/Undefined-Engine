#pragma once

#include <memory>

#include "service_locator.h"

#include "resources/texture.h"

#include "engine_debug/logger.h"

/// <summary>
/// Class to store all our framebuffer data
/// </summary>
class Framebuffer
{
public:
    /// <summary>
    /// Constructor for Framebuffer
    /// </summary>
    Framebuffer();
	/// <summary>
	/// Destructor for Framebuffer
	/// </summary>
	~Framebuffer();

    /// <summary>
    /// Rescale the framebuffer at the good window size
    /// </summary>
    /// <param name="width">: New width of the franebuffer</param>
    /// <param name="height">: New height of the framebuffer</param>
    void RescaleFramebuffer(unsigned int width, unsigned int height);

	/// <summary>
	/// Width of the framebuffer
	/// </summary>
	unsigned int Width;
	/// <summary>
	/// Height of the framebuffer
	/// </summary>
	unsigned int Height;

	/// <summary>
	/// ID of the framebuffer
	/// </summary>
	unsigned int FBO_ID;
	/// <summary>
	/// ID of the renderbuffer
	/// </summary>
	unsigned int RBO_ID;

	/// <summary>
	/// Framebuffer textures
	/// </summary>
	std::vector<std::unique_ptr<Texture>> FramebufferTextures;

private:
    /// <summary>
    /// Pointer to our Renderer to simplify the calls from the ServiceLocator
    /// </summary>
    Renderer* mRenderer = nullptr;

public:
    /// <summary>
    /// Create a Framebuffer
    /// </summary>
    /// <typeparam name="TextureNumber">: Number of Texture our framebuffer can store</typeparam>
    /// <param name="width">: Base width of the framebuffer</param>
    /// <param name="height">: Base height of the framebuffer</param>
    /// <returns>Return a pointer to the Framebuffer created</returns>
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

    glGenFramebuffers(1, &f->FBO_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, f->FBO_ID);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &f->RBO_ID);
    glBindRenderbuffer(GL_RENDERBUFFER, f->RBO_ID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, f->Width, f->Height); // use a single renderbuffer object for both a depth AND stencil buffer.

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, f->RBO_ID);

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

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, f->FramebufferTextures[i]->GetID(), 0);
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