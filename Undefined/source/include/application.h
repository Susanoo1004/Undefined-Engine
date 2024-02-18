#pragma once

#include "renderer/camera.h"
#include "Resources/texture.h"

class Application
{
public:
	Application();

	void Init();
	void Update();

	void InitQuad();

	Camera cam;

private:
	unsigned int quadVAO, quadVBO, quadEBO;
	unsigned int vertexShader, fragmentShader, shaderProgram;
};

