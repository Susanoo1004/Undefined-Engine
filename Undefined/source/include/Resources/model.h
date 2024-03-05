#pragma once

#include <vector>
#include <glad/glad.h>
#include <toolbox/Vector3.h>
#include <toolbox/Vector2.h>

#include "resources/resource.h"
#include "utils/flag.h"

struct IndexVertex
{
	unsigned int PosIndex;
	unsigned int NormalIndex;
	unsigned int TexIndex;
};

struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureUV;
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
	UNDEFINED_ENGINE bool IsValid();

	std::vector<Vertex> VertexBuffer;
	std::vector<IndexVertex> IndexBuffer;

private:
	unsigned int mVAO, mVBO, mEBO;
};