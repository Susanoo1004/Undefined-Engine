#pragma once

#include "wrapper/window_manager.h"
#include "wrapper/renderer.h"

class Singleton
{
public:
	static void Init();
	static void Destroy();

	static WindowManager* windowManager;
	static Renderer* renderer;
};