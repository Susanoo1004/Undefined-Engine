#pragma once

#include "camera/camera.h"
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
	unsigned int mVAO = 0, mVBO = 0, mEBO = 0;
	unsigned int mVertexShader = 0, mFragmentShader = 0, mShaderProgram = 0;
};

