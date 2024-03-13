#pragma once

#include <assimp/scene.h>

#include "resources/mesh.h"

class Model : public Resource
{
public:
    UNDEFINED_ENGINE Model();
    UNDEFINED_ENGINE Model(const char* path);

    UNDEFINED_ENGINE void Init();
    UNDEFINED_ENGINE void Draw();

    UNDEFINED_ENGINE bool IsValid() { return false; };

    UNDEFINED_ENGINE void SetTexture(int index, std::shared_ptr<Texture> tex);
private:
    // model data
    std::vector<std::pair<std::shared_ptr<Mesh>, std::shared_ptr<Texture>>> mModel;

    UNDEFINED_ENGINE void LoadModel(std::string path);
    UNDEFINED_ENGINE void ProcessNode(aiNode* node, const aiScene* scene);
    UNDEFINED_ENGINE Mesh ProcessMesh(aiMesh* mesh);

    unsigned int mVBO = 0, mEBO = 0, mVAO = 0;
};