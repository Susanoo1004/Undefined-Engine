#pragma once

#include "resources/texture.h"
#include "resources/shader.h"

#include "logger/logger.h"

#include "utils/flag.h"

#include "world/components/dir_light.h"

#include "resources/model.h"

#include "world/scene_manager/scene.h"
#include "world/scene_manager/object.h"
#include "world/components/player_test.h"

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
	Logger Log;
	DirLight DirectionalLight;

	// TODO: del
	Scene ActualScene;
	float T = 0;

private:
	unsigned int mVAO = 0, mVBO = 0, mEBO = 0;
	unsigned int mVertexShader = 0, mFragmentShader = 0, mShaderProgram = 0;

	Window* mWindowManager = nullptr;
	Renderer* mRenderer = nullptr;
};

