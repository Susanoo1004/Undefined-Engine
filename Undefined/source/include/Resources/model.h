#pragma once

#include <vector>
#include <glad/glad.h>

#include "resources/resource.h"
#include "TOSORT/Vertex.h"

class Model : public Resource
{
public:
	Model();
	Model(const std::string& filepath);
	~Model();

	void Draw();
	void LoadOBJ(const std::string& filepath);
	void SetOpenGL();

	std::vector<Vertex> vertexBuffer;
	std::vector<IndexVertex> indexBuffer;

private:
	unsigned int mVAO, mVBO, mEBO;
};