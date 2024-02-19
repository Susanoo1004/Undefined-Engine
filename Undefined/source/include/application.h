#pragma once

#include "renderer/camera.h"
#include "Resources/texture.h"

class Application
{
public:
	Application();

	void Init();
	void Update();

	void InitQuad();
	void InitVikingRoom();
	void Draw();

	Camera cam;

private:
	unsigned int mVAO, mVBO, mEBO = 0;
	unsigned int mVertexShader, mFragmentShader, mShaderProgram = 0;
};

