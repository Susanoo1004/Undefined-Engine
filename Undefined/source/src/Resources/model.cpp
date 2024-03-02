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
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertexBuffer.size());
}

void Model::LoadOBJ(const std::string& filepath)
{
	vertexBuffer.clear();
	indexBuffer.clear();

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
			sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex.posIndex, &indexVertex.texIndex, &indexVertex.normalIndex);
			indexBuffer.push_back(indexVertex);

			Vertex vertex;
			vertex.position = positions[indexVertex.posIndex - 1];
			vertex.textureUV = textureUvs[indexVertex.texIndex - 1];
			vertex.normal = normals[indexVertex.normalIndex - 1];
			vertexBuffer.push_back(vertex);

			newLine >> word;
			IndexVertex indexVertex2 = { 0,0,0 };
			sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex2.posIndex, &indexVertex2.texIndex, &indexVertex2.normalIndex);
			indexBuffer.push_back(indexVertex2);

			vertex.position = positions[indexVertex2.posIndex - 1];
			vertex.textureUV = textureUvs[indexVertex2.texIndex - 1];
			vertex.normal = normals[indexVertex2.normalIndex - 1];
			vertexBuffer.push_back(vertex);

			for (size_t i = 2; i < count; i++)
			{
				newLine >> word;
				IndexVertex indexVertex_i = { 0,0,0 };
				sscanf_s(word.c_str(), "%d/%d/%d", &indexVertex_i.posIndex, &indexVertex_i.texIndex, &indexVertex_i.normalIndex);
				indexBuffer.push_back(indexVertex_i);

				Vertex newVertex;
				newVertex.position = positions[indexVertex_i.posIndex - 1];
				newVertex.textureUV = textureUvs[indexVertex_i.texIndex - 1];
				newVertex.normal = normals[indexVertex_i.normalIndex - 1];
				vertexBuffer.push_back(newVertex);

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
	glGenBuffers(1, &mVBO);
	glGenVertexArrays(1, &mVAO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex),
		vertexBuffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureUV));
	glEnableVertexAttribArray(2);
}

bool Model::isValid()
{
	return (indexBuffer.size() > 0 && vertexBuffer.size() > 0);
}
