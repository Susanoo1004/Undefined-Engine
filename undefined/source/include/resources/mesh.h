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
};

class Mesh
{
public:
	UNDEFINED_ENGINE Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
};

