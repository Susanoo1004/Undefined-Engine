#pragma once

#include "framebuffer.h"

#include <toolbox/Vector2.h>

#include "resources/shader.h"

class EditorViewport
{
public:
	EditorViewport(Framebuffer* framebuffer, Camera* camera);
	~EditorViewport();

	void Init();
	void ShowWindow();

	unsigned int GetFBO_ID();

	Camera* ViewportCamera;
	Framebuffer* mFramebuffer;
private:
	std::shared_ptr<Shader> mShader;
	Vector2 mViewportBounds[2];

	unsigned int mEBO = 0, mVBO = 0, mVAO = 0;
	int mID;

private:
	static inline int mEditorNumber = 0;
};