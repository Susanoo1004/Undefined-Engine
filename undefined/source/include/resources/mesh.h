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

class UNDEFINED_ENGINE Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader& shader);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// can be change in an array of Texture*
	std::vector <Texture> textures;

private:
	unsigned int mVAO, mVBO, mEBO;

	void SetupMesh();
};

