#pragma once

#include <glad/glad.h>
#include <toolbox/Vector3.h>
#include <toolbox/Vector2.h>

#include "resources/texture.h"
#include "resources/shader.h"

#include "utils/flag.h"

/// <summary>
/// Struct to store the data we usually give to the shader
/// </summary>
struct Vertex
{
	/// <summary>
	/// Position of our vertex
	/// </summary>
	Vector3 Position;
	/// <summary>
	/// Normal of our vertex
	/// </summary>
	Vector3 Normal;
	/// <summary>
	/// UV Coordinates for our Textures
	/// </summary>
	Vector2 TexCoords;
};


class Mesh
{
public:
	/// <summary>
	/// Constructor of Mesh
	/// </summary>
	/// <param name="vertices">: std::vector of the vertices of our mesh</param>
	/// <param name="indices">: std::vector of the indices of our mesh</param>
	UNDEFINED_ENGINE Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
};

