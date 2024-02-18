#pragma once

#include "toolbox/Vector3.h"
#include "toolbox/Vector2.h"

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