#pragma once

#include <imgui/imgui.h>

#include "framebuffer.h"

#include "resources/shader.h"

class EditorViewport
{
public:
	EditorViewport(Framebuffer* framebuffer, Camera* camera);
	~EditorViewport();

	void Init();
	void ShowWindow();

	unsigned int GetFBO_ID() const;
	int GetEditorID() const;

	void RescaleViewport();

	Camera* ViewportCamera;

private:
	Framebuffer* mFramebuffer;
	std::shared_ptr<Shader> mShader;

	unsigned int mEBO = 0, mVBO = 0, mVAO = 0;
	int mID = 0;

	float mWidth = 0.f;
	float mHeight = 0.f;

private:
	static inline int mEditorNumber = 0;
};