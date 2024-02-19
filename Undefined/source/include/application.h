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
	void InitVikingRoom();
	void Draw();

	Camera cam;

private:
	unsigned int VAO, VBO, EBO = 0;
	unsigned int vertexShader, fragmentShader, shaderProgram = 0;
};

