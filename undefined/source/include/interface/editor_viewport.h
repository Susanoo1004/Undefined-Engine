#pragma once

#include <imgui/imgui.h>

#include "framebuffer.h"

#include "resources/shader.h"

class EditorViewport
{
public:
	/// <summary>
	/// Constructor of EditorViewport
	/// </summary>
	/// <param name="framebuffer">: Pointer to a Framebuffer</param>
	/// <param name="camera">: Pointer to a Camera</param>
	EditorViewport(Framebuffer* framebuffer, Camera* camera);
	/// <summary>
	/// Destructor of EditorViewport
	/// </summary>
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

	/// <summary>
	/// Pointer to the camera bind to the viewport
	/// </summary>
	Camera* ViewportCamera;

private:
	/// <summary>
	/// Pointer to the Framebuffer bind to the viewport
	/// </summary>
	Framebuffer* mFramebuffer;
	/// <summary>
	/// Pointer to the shader use by the viewport
	/// </summary>
	std::shared_ptr<Shader> mShader;

	/// <summary>
	/// EBO of the editor viewport
	/// </summary>
	unsigned int mEBO = 0;
	/// <summary>
	/// VBO of the editor viewport
	/// </summary>
	unsigned int mVBO = 0;
	/// <summary>
	/// VAO of the editor viewport
	/// </summary>
	unsigned int mVAO = 0;
	/// <summary>
	/// ID of the editor viewport
	/// </summary>
	int mID = 0;

	/// <summary>
	/// Width of the editor viewport
	/// </summary>
	float mWidth = 0.f;
	/// <summary>
	/// Height of the editor viewport
	/// </summary>
	float mHeight = 0.f;

private:
	/// <summary>
	/// Number of editor viewport from the beginning
	/// </summary>
	static inline int mEditorNumber = 0;
};