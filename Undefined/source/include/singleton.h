#pragma once

#include "wrapper_glfw.h"
#include "wrapper_RHI.h"

class Singleton
{
public:
	static void Init();
	static void Destroy();

	static WrapperGLFW* wrapperGLFW;
	static WrapperRHI* wrapperRHI;
};