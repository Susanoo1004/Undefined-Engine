#include "resources/model.h"

#include <fstream>
#include <string>
#include <sstream>

#include "logger/logger.h"
#include <glad/glad.h>

Model::Model()
{
	mVBO = 0;
	mVAO = 0;
	mEBO = 0;
}

Model::Model(const std::string& filepath)
{
	LoadOBJ(filepath);
}

Model::~Model()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void Model::Draw()
{
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)VertexBuffer.size());
}

void Model::LoadOBJ(const std::string& filepath)
{
	VertexBuffer.clear();
	IndexBuffer.clear();

	std::ifstream file(filepath);

	if (file.fail())
	{
		Logger::Warning("Model could not be loaded. filepath : {}", filepath);
	}

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
			{
				count++;
			}
			std::stringstream newLine(currentLine);
			newLine >> word >> word;

			IndexVertex indexVertex = { 0,0,0 };
			sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex.PosIndex, &indexVertex.TexIndex, &indexVertex.NormalIndex);
			IndexBuffer.push_back(indexVertex);

			Vertex vertex;
			vertex.Position = positions[indexVertex.PosIndex - 1];
			vertex.TextureUV = textureUvs[indexVertex.TexIndex - 1];
			vertex.Normal = normals[indexVertex.NormalIndex - 1];
			VertexBuffer.push_back(vertex);

			newLine >> word;
			IndexVertex indexVertex2 = { 0,0,0 };
			sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex2.PosIndex, &indexVertex2.TexIndex, &indexVertex2.NormalIndex);
			IndexBuffer.push_back(indexVertex2);

			vertex.Position = positions[indexVertex2.PosIndex - 1];
			vertex.TextureUV = textureUvs[indexVertex2.TexIndex - 1];
			vertex.Normal = normals[indexVertex2.NormalIndex - 1];
			VertexBuffer.push_back(vertex);

			for (size_t i = 2; i < count; i++)
			{
				newLine >> word;
				IndexVertex indexVertex_i = { 0,0,0 };
				sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex_i.PosIndex, &indexVertex_i.TexIndex, &indexVertex_i.NormalIndex);
				IndexBuffer.push_back(indexVertex_i);

				Vertex newVertex;
				newVertex.Position = positions[indexVertex_i.PosIndex - 1];
				newVertex.TextureUV = textureUvs[indexVertex_i.TexIndex - 1];
				newVertex.Normal = normals[indexVertex_i.NormalIndex - 1];
				VertexBuffer.push_back(newVertex);

				if (i + 1 == count)
				{
					break;
				}

				IndexBuffer.push_back(indexVertex);
				IndexBuffer.push_back(indexVertex_i);
			}
		}
	}
	file.close();

	SetOpenGL();
}

// HAS TO BE MOVE IN RENDERER OR AT LEAST CALL A RENDERER FUNCTION
void Model::SetOpenGL()
{
	glGenBuffers(1, &mVBO);
	glGenVertexArrays(1, &mVAO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, VertexBuffer.size() * sizeof(Vertex),
		VertexBuffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureUV));
	glEnableVertexAttribArray(2);
}

bool Model::IsValid()
{
	return (IndexBuffer.size() > 0 && VertexBuffer.size() > 0);
}
