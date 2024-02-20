#pragma once

#include <glad/glad.h>

#include "engine_debug/renderer_debug.h"

class Renderer
{
public:
	void WrapperInit(float redBaseColor = 0.3f, float greenBaseColor = 0.3f, float blueBaseColor = 0.3f);

	void SetClearColor(GLbitfield mask);
	
	//Texture
	void BindTexture(unsigned int ID);

	RendererDebug debug;
private:
};

