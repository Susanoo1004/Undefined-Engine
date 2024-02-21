#pragma once

#include <vector>
#include <glad/glad.h>
#include <toolbox/Vector3.h>
#include <toolbox/Vector2.h>

#include "resources/resource.h"

struct IndexVertex
{
	unsigned int posIndex;
	unsigned int normalIndex;
	unsigned int texIndex;
};

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 textureUV;
};

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