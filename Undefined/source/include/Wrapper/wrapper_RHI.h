#pragma once

#include <glad/glad.h>

#include "engine_debug/RHI_debug.h"

class WrapperRHI
{
public:
	void WrapperInit(float redBaseColor = 0.3f, float greenBaseColor = 0.3f, float blueBaseColor = 0.3f);

	void SetClearColor(GLbitfield mask);
	
	//Texture
	void BindTexture(unsigned int ID);

	RHIDebug debug;
private:
};

