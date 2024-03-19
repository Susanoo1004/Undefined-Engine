#pragma once

#include "resources/texture.h"
#include "resources/shader.h"

#include "logger/logger.h"

#include "utils/flag.h"

#include "world/component/dir_light.h"

#include "resources/model.h"

class Window;
class Renderer;

class Application
{
public:
	UNDEFINED_ENGINE Application();

	UNDEFINED_ENGINE void Init();
	UNDEFINED_ENGINE void Update();
	UNDEFINED_ENGINE void Clear();

	UNDEFINED_ENGINE void InitQuad();
	UNDEFINED_ENGINE void Draw();

	std::shared_ptr<Shader> BaseShader;
	std::shared_ptr<Shader> skyboxShader;

	Logger Log;
	DirLight DirectionalLight;

	// to del
	float T = 0;

private:
	unsigned int mVAO = 0, mVBO = 0, mEBO = 0;
	unsigned int mVertexShader = 0, mFragmentShader = 0, mShaderProgram = 0;

	Window* mWindowManager = nullptr;
	Renderer* mRenderer = nullptr;

public:
	UNDEFINED_ENGINE static inline bool IsInGame = false;
};

