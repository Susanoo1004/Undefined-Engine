#pragma once

#include <vector>
#include <glad/glad.h>

#include "Resources/resource.h"
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
	unsigned int m_VAO, m_VBO, m_EBO;
};