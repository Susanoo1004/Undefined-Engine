#pragma once

#include "Wrapper/wrapper_glfw.h"
#include "Wrapper/wrapper_RHI.h"

class Singleton
{
public:
	static void Init();
	static void Destroy();

	static WrapperGLFW* wrapperGLFW;
	static WrapperRHI* wrapperRHI;
};