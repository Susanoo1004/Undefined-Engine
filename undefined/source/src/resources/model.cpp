#include "resources/model.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "resources/resource_manager.h"

#include "service_locator.h"

Model::Model()
{
    Render = nullptr;
}

Model::Model(const char* path)
{
    Render = ServiceLocator::Get<Renderer>();

	LoadModel(path);

    Init();
}

void Model::Init()
{
    Render->GenerateVertexArray(1, &mVAO);
    Render->GenerateBuffer(1, &mVBO);
    Render->GenerateBuffer(1, &mEBO);

    Render->BindBuffers(mVAO, mVBO, mEBO);

    // vertex positions
    Render->AttributePointers(0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);

    // vertex normals
    Render->AttributePointers(1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // vertex texture coords
    Render->AttributePointers(2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    Render->BindBuffers(0, 0, 0);
}
void Model::Draw()
{
    Render->BindBuffers(mVAO, mVBO, mEBO);

    for (std::pair<std::shared_ptr<Mesh>, std::shared_ptr<Texture>> pair : mModel)
    {
        Render->SetBufferData(GL_ARRAY_BUFFER, (int)pair.first->Vertices.size() * sizeof(Vertex), &pair.first->Vertices[0], GL_STATIC_DRAW);
        Render->SetBufferData(GL_ELEMENT_ARRAY_BUFFER, (int)pair.first->Indices.size() * sizeof(unsigned int), &pair.first->Indices[0], GL_STATIC_DRAW);

        if (pair.second)
        {
            Render->BindTexture(pair.second->GetID());
        }
        else
        {
            Render->BindTexture(ResourceManager::Get<Texture>("assets/missing_texture.jpg")->GetID());
        }

        Render->Draw(GL_TRIANGLES, (GLsizei)pair.first->Indices.size(), GL_UNSIGNED_INT, 0);
    }
    
    Render->BindBuffers(0, 0, 0);
    Render->BindTexture(0);
}

void Model::SetTexture(int index, std::shared_ptr<Texture> tex)
{
    mModel[index].second = tex;
}

void Model::LoadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::Error("ERROR::ASSIMP:: {} ", import.GetErrorString());
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        mModel.push_back(std::make_pair<std::shared_ptr<Mesh>, std::shared_ptr<Texture>>(std::make_shared<Mesh>(ProcessMesh(mesh)), nullptr));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh)
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        // process vertex positions, normals and texture coordinates
        Vector3 v;
        v.x = mesh->mVertices[i].x;
        v.y = mesh->mVertices[i].y;
        v.z = mesh->mVertices[i].z;
        vertex.Position = v;

        v.x = mesh->mNormals[i].x;
        v.y = mesh->mNormals[i].y;
        v.z = mesh->mNormals[i].z;
        vertex.Normal = v;

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            Vector2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = Vector2(0.0f, 0.0f);
        }

        Vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            Indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(Vertices, Indices);
}