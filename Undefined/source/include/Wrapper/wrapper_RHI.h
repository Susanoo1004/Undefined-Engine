#pragma once

#include <glad/glad.h>

#include "Debug/RHI_debug.h"

class WrapperRHI
{
public:
	void WrapperInit(float redBaseColor = 0.3f, float greenBaseColor = 0.3f, float blueBaseColor = 0.3f);

	void SetClearColor(GLbitfield mask);

	RHIDebug debug;
private:
};

