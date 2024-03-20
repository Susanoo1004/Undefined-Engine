#pragma once

#include "framebuffer.h"

class EditorViewport
{
public:
	EditorViewport(Framebuffer* framebuffer);
	~EditorViewport();


	void Init();
	void ShowWindow();

private:
	Framebuffer* mFramebuffer;
};