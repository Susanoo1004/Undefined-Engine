#pragma once

#include "resources/texture.h"
#include "resources/shader.h"

#include "engine_debug/logger.h"

#include "audio/sound_device.h"
#include "audio/sound_source.h"

#include "utils/flag.h"

class Window;
class Renderer;
class Object;

class Application
{
public:
	UNDEFINED_ENGINE Application();

	UNDEFINED_ENGINE void Init();
	UNDEFINED_ENGINE void Update();
	UNDEFINED_ENGINE void Clear();

	std::shared_ptr<Shader> BaseShader;

	Logger Log;

private:
	Window* mWindowManager = nullptr;
	Renderer* mRenderer = nullptr;
	SoundDevice* mSoundDevice = nullptr;
	std::shared_ptr<KeyInput> mKeyInput = nullptr;
	SoundSource* mSoundSource = nullptr;
	uint32_t source1 = 0;
	uint32_t source2 = 0;
	uint32_t sound1 = 0;
	uint32_t sound2 = 0;

public:
	UNDEFINED_ENGINE static inline bool IsInGame = false;
};

