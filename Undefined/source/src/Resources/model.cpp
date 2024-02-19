#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>

#include "Resources/model.h"

Model::Model()
{
}

Model::Model(const std::string& filepath)
{
	LoadOBJ(filepath);
}

Model::~Model()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Model::Draw()
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.size());
}

void Model::LoadOBJ(const std::string& filepath)
{

	vertexBuffer.clear();
	indexBuffer.clear();

	std::ifstream file(filepath);

	// ASSERT(file.good());

	std::string currentLine;
	std::string word;

	std::vector<Vector3> positions, normals;
	std::vector<Vector2> textureUvs;

	while (std::getline(file, currentLine))
	{
		std::stringstream line(currentLine);
		line >> word;

		if (word == "v")
		{
			Vector3 pos;
			line >> pos.x >> pos.y >> pos.z;
			positions.push_back(pos);
		}
		else if (word == "vt")
		{
			Vector2 Uv;
			line >> Uv.x >> Uv.y;
			textureUvs.push_back(Uv);
		}
		else if (word == "vn")
		{
			Vector3 normal;
			line >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (word == "f")
		{
			int count = 0;
			while (line >> word)
				count++;
			std::stringstream line(currentLine);
			line >> word >> word;

			IndexVertex indexVertex = { 0,0,0 };
			sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex.PosIndex, &indexVertex.TexIndex, &indexVertex.NormalIndex);
			indexBuffer.push_back(indexVertex);

			Vertex vertex;
			vertex.Position = positions[indexVertex.PosIndex - 1];
			vertex.TextureUV = textureUvs[indexVertex.TexIndex - 1];
			vertex.Normal = normals[indexVertex.NormalIndex - 1];
			vertexBuffer.push_back(vertex);

			line >> word;
			IndexVertex indexVertex2 = { 0,0,0 };
			sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex2.PosIndex, &indexVertex2.TexIndex, &indexVertex2.NormalIndex);
			indexBuffer.push_back(indexVertex2);

			vertex.Position = positions[indexVertex2.PosIndex - 1];
			vertex.TextureUV = textureUvs[indexVertex2.TexIndex - 1];
			vertex.Normal = normals[indexVertex2.NormalIndex - 1];
			vertexBuffer.push_back(vertex);

			for (size_t i = 2; i < count; i++)
			{
				line >> word;
				IndexVertex indexVertex_i = { 0,0,0 };
				sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex_i.PosIndex, &indexVertex_i.TexIndex, &indexVertex_i.NormalIndex);
				indexBuffer.push_back(indexVertex_i);

				Vertex vertex;
				vertex.Position = positions[indexVertex_i.PosIndex - 1];
				vertex.TextureUV = textureUvs[indexVertex_i.TexIndex - 1];
				vertex.Normal = normals[indexVertex_i.NormalIndex - 1];
				vertexBuffer.push_back(vertex);

				if (i + 1 == count)
				{
					break;
				}

				indexBuffer.push_back(indexVertex);
				indexBuffer.push_back(indexVertex_i);
			}
		}
	}
	file.close();

	SetOpenGL();
}

void Model::SetOpenGL()
{
	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex),
		vertexBuffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureUV));
	glEnableVertexAttribArray(2);
}