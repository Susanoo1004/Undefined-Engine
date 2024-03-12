#pragma once

#include <assimp/scene.h>

#include "resources/mesh.h"

class Model
{
public:
    UNDEFINED_ENGINE Model();
    UNDEFINED_ENGINE Model(const char* path);
    UNDEFINED_ENGINE void Draw(Shader& shader);

    UNDEFINED_ENGINE bool IsValid() { return false; };
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    UNDEFINED_ENGINE void LoadModel(std::string path);
    UNDEFINED_ENGINE void ProcessNode(aiNode* node, const aiScene* scene);
    UNDEFINED_ENGINE Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

};