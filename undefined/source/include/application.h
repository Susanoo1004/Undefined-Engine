#pragma once

#include "resources/texture.h"
#include "resources/shader.h"

#include "engine_debug/logger.h"

#include "audio/sound_device.h"
#include "audio/sound_source.h"

#include "utils/flag.h"

class Window;
class Renderer;

class Application
{
public:
	UNDEFINED_ENGINE Application();

	UNDEFINED_ENGINE void Init();
	UNDEFINED_ENGINE void Update();
	UNDEFINED_ENGINE void Clear();

	std::shared_ptr<Shader> BaseShader;
	std::shared_ptr<Shader> skyboxShader;
	std::shared_ptr<Shader> pickingShader;

	Logger Log;

private:
	unsigned int mVAO = 0, mVBO = 0, mEBO = 0;
	unsigned int mVertexShader = 0, mFragmentShader = 0, mShaderProgram = 0;

	Window* mWindowManager = nullptr;
	Renderer* mRenderer = nullptr;
	SoundDevice* mSoundDevice = nullptr;
	std::shared_ptr<KeyInput> mKeyInput = nullptr;
	SoundSource* tamerelaputemaxime;

public:
	UNDEFINED_ENGINE static inline bool IsInGame = false;
};

