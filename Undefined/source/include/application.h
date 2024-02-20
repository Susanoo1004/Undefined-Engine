#pragma once

#include "camera/camera.h"
#include "Resources/texture.h"
#include "resources/shader.h"
#include "logger/logger.h"

class Application
{
public:
	Application();

	void Init();
	void Update();

	void InitQuad();
	void InitBaseShader();
	void InitVikingRoom();
	void Draw();

	Camera cam;

	Shader baseShader;
	Logger log;

private:
	unsigned int mVAO = 0, mVBO = 0, mEBO = 0;
	unsigned int mVertexShader = 0, mFragmentShader = 0, mShaderProgram = 0;
};

