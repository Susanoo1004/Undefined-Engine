#pragma once

#include <vector>
#include <glad/glad.h>
#include <toolbox/Vector3.h>
#include <toolbox/Vector2.h>

#include "resources/resource.h"
#include "utils/flag.h"

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
	UNDEFINED_ENGINE Model();
	UNDEFINED_ENGINE Model(const std::string& filepath);
	UNDEFINED_ENGINE ~Model();

	UNDEFINED_ENGINE void Draw();
	UNDEFINED_ENGINE void LoadOBJ(const std::string& filepath);
	UNDEFINED_ENGINE void SetOpenGL();
	UNDEFINED_ENGINE bool isValid();

	std::vector<Vertex> vertexBuffer;
	std::vector<IndexVertex> indexBuffer;

private:
	unsigned int mVAO, mVBO, mEBO;
};