#pragma once

#include <imgui/imgui.h>

#include "framebuffer.h"

#include "resources/shader.h"

class EditorViewport
{
public:
	EditorViewport(Framebuffer* framebuffer, Camera* camera);
	~EditorViewport();

	/// <summary>
	/// Init the editor viewport
	/// </summary>
	void Init();
	/// <summary>
	/// Display the window with the needed inside
	/// </summary>
	void ShowWindow();

	/// <summary>
	/// Get the framebuffer ID
	/// </summary>
	/// <returns>Return the framebuffer ID</returns>
	unsigned int GetFBO_ID() const;
	/// <summary>
	/// Get the editor ID
	/// </summary>
	/// <returns>Return the editor ID</returns>
	int GetEditorID() const;

	/// <summary>
	/// Rescale the viewport with the current window size
	/// </summary>
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