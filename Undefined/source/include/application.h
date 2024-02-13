#pragma once

class Application
{
public:
	void Init();
	void Update();

	void InitQuad();

private:
	unsigned int quadVAO, quadVBO, quadEBO;
	unsigned int vertexShader, fragmentShader, shaderProgram;
};

