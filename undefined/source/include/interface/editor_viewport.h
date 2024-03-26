#pragma once

#include "framebuffer.h"

#include "resources/shader.h"

class EditorViewport
{
public:
	EditorViewport(Framebuffer* framebuffer);
	~EditorViewport();

	void Init();
	void ShowWindow();

	unsigned int GetFBO_ID();

private:
	Framebuffer* mFramebuffer;
	std::shared_ptr<Shader> mShader;

	unsigned int mEBO = 0, mVBO = 0, mVAO = 0;
};