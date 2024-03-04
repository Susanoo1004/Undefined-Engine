#pragma once

#include "camera/camera.h"

#include "resources/texture.h"
#include "resources/shader.h"

#include "logger/logger.h"

#include "utils/flag.h"

#include "world/component/dir_light.h"

class Application
{
public:
	UNDEFINED_ENGINE Application();

	UNDEFINED_ENGINE void Init();
	UNDEFINED_ENGINE void Update();

	UNDEFINED_ENGINE void InitQuad();
	UNDEFINED_ENGINE void InitVikingRoom();
	UNDEFINED_ENGINE void Draw();

	Camera cam;

	Shader baseShader;
	Logger log;

	DirLight dirLight;

	// to del
	float t = 0;

private:
	unsigned int mVAO = 0, mVBO = 0, mEBO = 0;
	unsigned int mVertexShader = 0, mFragmentShader = 0, mShaderProgram = 0;
};

