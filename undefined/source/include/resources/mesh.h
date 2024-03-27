#pragma once

#include <glad/glad.h>
#include <toolbox/Vector3.h>
#include <toolbox/Vector2.h>

#include "resources/texture.h"
#include "resources/shader.h"

#include "utils/flag.h"

struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TexCoords;
	int EntityID;
};

class Mesh
{
public:
	UNDEFINED_ENGINE Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
};

