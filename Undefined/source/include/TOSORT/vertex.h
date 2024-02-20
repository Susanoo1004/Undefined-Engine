#pragma once

#include <toolbox/Vector3.h>
#include <toolbox/Vector2.h>

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